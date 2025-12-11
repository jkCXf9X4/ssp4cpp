from __future__ import annotations

from dataclasses import replace
from pathlib import Path
from typing import Dict, List, Optional, Tuple
import xml.etree.ElementTree as ET

from misc import (
    FieldDefinition,
    TypeDefinition,
    sanitize,
    pluralize,
    split_qname,
    NS,
    XSD_NS,
    PRIMITIVE_TYPES,
)


class XsdParser:
    def __init__(self, schema_dir: Path, default_namespace: str = "") -> None:
        self.schema_dir = schema_dir
        self.default_namespace = default_namespace
        self.simple_types: Dict[Tuple[str, str], str] = {}
        self.attribute_groups: Dict[Tuple[str, str], List[FieldDefinition]] = {}
        self.types: Dict[Tuple[str, str], TypeDefinition] = {}

    def parse(self) -> None:
        for path in sorted(self.schema_dir.glob("*.xsd")):
            self._parse_file(path)

    def _parse_file(self, path: Path) -> None:
        tree = ET.parse(path)
        root = tree.getroot()
        ns_map = self._extract_namespace_map(root)
        target_namespace_uri = root.attrib.get("targetNamespace")
        target_prefix = self._prefix_for_namespace(ns_map, target_namespace_uri)
        target = target_prefix or self.default_namespace

        for simple_type in root.findall("xs:simpleType", NS):
            self._register_simple_type(simple_type, target)

        for attribute_group in root.findall("xs:attributeGroup", NS):
            self._register_attribute_group(attribute_group, target)

        for complex_type in root.findall("xs:complexType", NS):
            if "name" not in complex_type.attrib:
                continue
            type_def = self._parse_complex_type(
                complex_type, target, ns_map, complex_type.attrib["name"]
            )
            self._register_type(type_def)

        for element in root.findall("xs:element", NS):
            self._register_element(element, target, ns_map)

    def _extract_namespace_map(self, root: ET.Element) -> Dict[str, str]:
        ns_map = {}
        for key, value in root.attrib.items():
            if not key.startswith("{http://www.w3.org/2000/xmlns/}"):
                continue
            prefix = key.split("}", 1)[1]
            ns_map[prefix] = value
        return ns_map

    def _prefix_for_namespace(
        self, ns_map: Dict[str, str], namespace_uri: Optional[str]
    ) -> Optional[str]:
        if not namespace_uri:
            return None
        for prefix, uri in ns_map.items():
            if uri == namespace_uri:
                return prefix
        return None

    def _register_simple_type(self, node: ET.Element, namespace: str) -> None:
        name = node.attrib.get("name")
        if not name:
            return
        restriction = node.find("xs:restriction", NS)
        if restriction is None:
            return
        base = restriction.attrib.get("base")
        if not base:
            return
        _, local_base = split_qname(base)
        self.simple_types[(namespace, name)] = PRIMITIVE_TYPES.get(local_base, name)

    def _register_attribute_group(self, node: ET.Element, namespace: str) -> None:
        name = node.attrib.get("name")
        if not name:
            return
        fields: List[FieldDefinition] = []
        for child in node:
            if child.tag == f"{{{XSD_NS}}}attribute":
                fields.append(
                    self._parse_attribute(child, namespace, {}, namespace, None)
                )
            elif child.tag == f"{{{XSD_NS}}}attributeGroup":
                ref = child.attrib.get("ref")
                if ref:
                    fields.extend(self._resolve_attribute_group(ref, namespace))
        self.attribute_groups[(namespace, name)] = fields

    def _register_type(self, type_def: TypeDefinition) -> None:
        key = (type_def.namespace, type_def.name)
        if key not in self.types:
            self.types[key] = type_def

    def _register_element(
        self, element: ET.Element, namespace: str, ns_map: Dict[str, str]
    ) -> None:
        name = element.attrib.get("name")
        if not name:
            return
        complex_type = element.find("xs:complexType", NS)
        if complex_type is None:
            return
        type_def = self._parse_complex_type(complex_type, namespace, ns_map, name)
        self._register_type(type_def)

    def _parse_complex_type(
        self,
        node: ET.Element,
        namespace: str,
        ns_map: Dict[str, str],
        name_hint: str,
        type_prefix: Optional[str] = None,
    ) -> TypeDefinition:
        fields: List[FieldDefinition] = []
        for child in node:
            if child.tag == f"{{{XSD_NS}}}sequence":
                fields.extend(
                    self._parse_sequence(child, namespace, ns_map, type_prefix)
                )
            elif child.tag == f"{{{XSD_NS}}}choice":
                fields.extend(
                    self._parse_sequence(child, namespace, ns_map, type_prefix)
                )
            elif child.tag == f"{{{XSD_NS}}}attribute":
                fields.append(
                    self._parse_attribute(
                        child, namespace, ns_map, namespace, type_prefix
                    )
                )
            elif child.tag == f"{{{XSD_NS}}}attributeGroup":
                ref = child.attrib.get("ref")
                if ref:
                    fields.extend(self._resolve_attribute_group(ref, namespace))
            elif child.tag == f"{{{XSD_NS}}}complexContent":
                extension = child.find("xs:extension", NS)
                if extension is not None:
                    base = extension.attrib.get("base")
                    if base:
                        base_fields = self._fields_from_base(base, namespace)
                        fields.extend(base_fields)
                    fields.extend(
                        self._parse_complex_type(
                            extension, namespace, ns_map, name_hint, type_prefix
                        ).fields
                    )
        return TypeDefinition(name=name_hint, namespace=namespace, fields=fields)

    def _parse_sequence(
        self,
        node: ET.Element,
        namespace: str,
        ns_map: Dict[str, str],
        type_prefix: Optional[str],
    ) -> List[FieldDefinition]:
        fields: List[FieldDefinition] = []
        for element in node.findall("xs:element", NS):
            name = element.attrib.get("name")
            if not name:
                continue
            original_name = name
            min_occurs = element.attrib.get("minOccurs", "1")
            max_occurs = element.attrib.get("maxOccurs", "1")
            is_list = max_occurs not in ("1", None)
            optional = min_occurs == "0"

            sanitized = sanitize(original_name)
            field_name = pluralize(sanitized) if is_list else sanitized
            xml_tag = original_name if field_name != original_name else None

            field_type, field_type_prefix, field_ns, type_namespace = (
                self._resolve_element_type(element, namespace, ns_map, type_prefix)
            )

            fields.append(
                FieldDefinition(
                    name=field_name,
                    type_name=field_type,
                    optional=optional,
                    is_list=is_list,
                    type_prefix=field_type_prefix,
                    type_namespace=type_namespace,
                    namespace=field_ns,
                    xml_tag=xml_tag,
                )
            )
        return fields

    def _parse_attribute(
        self,
        node: ET.Element,
        namespace: str,
        ns_map: Dict[str, str],
        default_namespace: str,
        type_prefix: Optional[str],
    ) -> FieldDefinition:
        name = node.attrib["name"]
        sanitized = sanitize(name)
        use = node.attrib.get("use", "optional")
        optional = use != "required"
        xml_tag = name if sanitized != name else None
        field_ns = None

        type_name_attr = node.attrib.get("type")
        field_type, field_type_prefix = self._resolve_type(
            type_name_attr, default_namespace, type_prefix
        )

        if field_type is None:
            simple_type = node.find("xs:simpleType", NS)
            if simple_type is not None:
                field_type, field_type_prefix = self._resolve_inline_simple_type(
                    simple_type, default_namespace, type_prefix
                )
                field_type_prefix = field_type_prefix or type_prefix
            else:
                field_type = "string"

        ref_prefix, _ = split_qname(type_name_attr) if type_name_attr else (None, None)
        type_namespace = ref_prefix or default_namespace or None

        return FieldDefinition(
            name=sanitized,
            type_name=field_type,
            optional=optional,
            type_prefix=field_type_prefix,
            type_namespace=type_namespace,
            namespace=field_ns,
            xml_tag=xml_tag,
        )

    def _resolve_inline_simple_type(
        self, node: ET.Element, namespace: str, type_prefix: Optional[str]
    ) -> Tuple[str, Optional[str]]:
        restriction = node.find("xs:restriction", NS)
        if restriction is not None:
            base = restriction.attrib.get("base")
            base_type, base_prefix = self._resolve_type(base, namespace, type_prefix)
            if base_type:
                return base_type, base_prefix
        return "string", None

    def _resolve_element_type(
        self,
        element: ET.Element,
        namespace: str,
        ns_map: Dict[str, str],
        type_prefix: Optional[str],
    ) -> Tuple[str, Optional[str], Optional[str], Optional[str]]:
        type_attr = element.attrib.get("type")
        if type_attr:
            field_type, field_type_prefix = self._resolve_type(
                type_attr, namespace, type_prefix
            )
            if field_type:
                ref_ns, _ = split_qname(type_attr)
                return field_type, field_type_prefix, namespace, ref_ns or namespace

        complex_type = element.find("xs:complexType", NS)
        if complex_type is not None:
            inline_type_name = sanitize(element.attrib["name"])
            type_def = self._parse_complex_type(
                complex_type, namespace, ns_map, inline_type_name, type_prefix
            )
            self._register_type(type_def)
            return (
                type_def.name,
                namespace or type_prefix,
                namespace or None,
                namespace or None,
            )

        simple_type = element.find("xs:simpleType", NS)
        if simple_type is not None:
            base_type, base_prefix = self._resolve_inline_simple_type(
                simple_type, namespace, type_prefix
            )
            return base_type, base_prefix, namespace, namespace or None

        return "string", None, namespace, namespace or None

    def _resolve_type(
        self,
        type_name: Optional[str],
        namespace: str,
        type_prefix: Optional[str],
    ) -> Tuple[Optional[str], Optional[str]]:
        if not type_name:
            return None, None
        prefix, local = split_qname(type_name)
        primitive = PRIMITIVE_TYPES.get(local)
        if primitive:
            return primitive, None

        target_ns = prefix or namespace
        if (target_ns, local) in self.simple_types:
            return local, target_ns or type_prefix

        if prefix:
            return local, prefix

        return local, type_prefix or namespace or None

    def _fields_from_base(self, base: str, namespace: str) -> List[FieldDefinition]:
        prefix, local = split_qname(base)
        key = (prefix or namespace, local)
        base_type = self.types.get(key)
        if not base_type:
            return []
        return [replace(f) for f in base_type.fields]

    def _resolve_attribute_group(
        self, ref: str, current_namespace: str
    ) -> List[FieldDefinition]:
        prefix, local = split_qname(ref)
        key = (prefix or current_namespace, local)
        fields = self.attribute_groups.get(key, [])
        return [replace(f) for f in fields]
