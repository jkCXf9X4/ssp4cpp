from __future__ import annotations

import argparse
from dataclasses import dataclass, field, replace
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple
import xml.etree.ElementTree as ET

XSD_NS = "http://www.w3.org/2001/XMLSchema"
NS = {"xs": XSD_NS}


PRIMITIVE_TYPES = {
    "string": "string",
    "normalizedString": "string",
    "token": "string",
    "anyURI": "string",
    "ID": "string",
    "Name": "string",
    "NCName": "string",
    "language": "string",
    "dateTime": "string",
    "int": "int",
    "integer": "int",
    "long": "int",
    "unsignedInt": "unsigned int",
    "unsignedLong": "unsigned int",
    "positiveInteger": "unsigned int",
    "double": "double",
    "float": "double",
    "boolean": "bool",
}


def sanitize(name: str) -> str:
    return name.replace("-", "_")


def pluralize(name: str) -> str:
    if name.endswith("s"):
        return name
    return f"{name}s"


def split_qname(name: str) -> Tuple[Optional[str], str]:
    if ":" in name:
        prefix, local = name.split(":", 1)
        return prefix, local
    return None, name


def format_type_name(name: str, prefix: Optional[str]) -> str:
    if not prefix:
        return name
    if prefix.endswith("::"):
        return f"{prefix}{name}"
    if "::" in prefix:
        return f"{prefix}::{name}"
    return f"{prefix}::{name}"


@dataclass
class FieldDefinition:
    name: str
    type_name: str
    optional: bool = False
    is_list: bool = False
    type_prefix: Optional[str] = None
    type_namespace: Optional[str] = None
    namespace: Optional[str] = None
    xml_tag: Optional[str] = None

    def copy_with(self, **kwargs) -> "FieldDefinition":
        return replace(self, **kwargs)


@dataclass
class TypeDefinition:
    name: str
    namespace: str
    fields: List[FieldDefinition] = field(default_factory=list)


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

    def _register_attribute_group(
        self, node: ET.Element, namespace: str
    ) -> None:
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
        type_def = self._parse_complex_type(
            complex_type, namespace, ns_map, name
        )
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
                    self._parse_attribute(child, namespace, ns_map, namespace, type_prefix)
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

            field_type, field_type_prefix, field_ns, type_namespace = self._resolve_element_type(
                element, namespace, ns_map, type_prefix
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
            return type_def.name, namespace or type_prefix, namespace or None, namespace or None

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


def type_is_primitive(type_name: str) -> bool:
    return type_name in PRIMITIVE_TYPES.values()


def render_header(task: "SchemaTask") -> List[str]:
    lines = [
        f'aaa_standard = "{task.standard}"',
        f'aaa_namespace = "{task.namespace}"',
        f'aaa_name = "{task.name}"',
    ]
    if task.headers:
        quoted = ', '.join(f'"{h}"' for h in task.headers)
        lines.append(f"aaa_headers = [{quoted}]")
    if task.dependencies:
        quoted = ', '.join(f'"{d}"' for d in task.dependencies)
        lines.append(f"aaa_dependencies = [{quoted}]")
    if task.forward_declarations:
        quoted = ', '.join(f'"{d}"' for d in task.forward_declarations)
        lines.append(f"aaa_forward_declarations = [{quoted}]")
    return lines


def render_type(type_def: TypeDefinition, type_prefix: Optional[str]) -> List[str]:
    lines = [f"[{type_def.name}]"]
    for field in type_def.fields:
        is_primitive = type_is_primitive(field.type_name)
        prefix = field.type_prefix or type_prefix
        type_value = field.type_name if is_primitive else format_type_name(field.type_name, prefix)

        parts = [f'type = "{type_value}"']
        if field.optional:
            parts.append("optional = true")
        if field.is_list:
            parts.append("list = true")
        if field.namespace:
            parts.append(f'namespace="{field.namespace}"')
        if field.xml_tag:
            parts.append(f'xml_tag="{field.xml_tag}"')

        lines.append(f"{field.name} = " + "{ " + ", ".join(parts) + " }")
    return lines


def reachable_types(
    types: Dict[Tuple[str, str], TypeDefinition],
    roots: Iterable[str],
    namespace: str,
) -> List[TypeDefinition]:
    wanted: Dict[Tuple[str, str], TypeDefinition] = {}
    queue = list(roots)
    visited = set()

    while queue:
        name = queue.pop(0)
        key = (namespace, name)
        if key in visited:
            continue
        visited.add(key)

        type_def = types.get(key)
        if not type_def:
            continue

        wanted[key] = type_def
        for field in type_def.fields:
            if type_is_primitive(field.type_name):
                continue
            target_ns = field.type_namespace or namespace
            if target_ns != namespace:
                continue
            queue.append(field.type_name)
    return list(wanted.values())


def render_toml(task: "SchemaTask", types: List[TypeDefinition]) -> str:
    lines: List[str] = []
    lines.extend(render_header(task))
    lines.append("")
    for type_def in sorted(types, key=lambda t: t.name):
        lines.extend(render_type(type_def, task.type_prefix))
        lines.append("")
    return "\n".join(lines).rstrip() + "\n"


def root_elements_from_schema(schema: Path) -> List[str]:
    tree = ET.parse(schema)
    root = tree.getroot()
    return [el.attrib["name"] for el in root.findall("xs:element", NS) if "name" in el.attrib]


@dataclass
class SchemaTask:
    standard: str
    namespace: str
    name: str
    schema_root: Path
    output: Path
    headers: List[str] = field(default_factory=list)
    dependencies: List[str] = field(default_factory=list)
    forward_declarations: List[str] = field(default_factory=list)
    type_prefix: Optional[str] = None
    root_types: Optional[List[str]] = None

    @property
    def schema_dir(self) -> Path:
        return self.schema_root.parent


def load_presets(repo_root: Path) -> Dict[str, SchemaTask]:
    return {
        "ssp1-ssd": SchemaTask(
            standard="SSP1",
            namespace="ssd",
            name="SystemStructureDescription",
            schema_root=repo_root / "3rdParty/SSP1/schema/SystemStructureDescription.xsd",
            output=repo_root / "resources/ssp1_ssd.toml",
            headers=["FMI2_Enums.hpp", "SSP1_Enums.hpp"],
            dependencies=[
                "SSP1_SystemStructureCommon",
                "SSP1_SystemStructureParameterMapping",
                "SSP1_SystemStructureParameterValues",
            ],
            forward_declarations=["class TSystem;"],
            type_prefix="ssd",
        ),
        "ssp1-ssc": SchemaTask(
            standard="SSP1",
            namespace="ssc",
            name="SystemStructureCommon",
            schema_root=repo_root / "3rdParty/SSP1/schema/SystemStructureCommon.xsd",
            output=repo_root / "resources/ssp1_ssc.toml",
            headers=["SSP1_Enums.hpp"],
            type_prefix="ssc",
        ),
        "ssp1-ssv": SchemaTask(
            standard="SSP1",
            namespace="ssv",
            name="SystemStructureParameterValues",
            schema_root=repo_root / "3rdParty/SSP1/schema/SystemStructureParameterValues.xsd",
            output=repo_root / "resources/ssp1_ssv.toml",
            dependencies=["SSP1_SystemStructureCommon"],
            type_prefix="ssv",
        ),
        "ssp1-ssm": SchemaTask(
            standard="SSP1",
            namespace="ssm",
            name="SystemStructureParameterMapping",
            schema_root=repo_root / "3rdParty/SSP1/schema/SystemStructureParameterMapping.xsd",
            output=repo_root / "resources/ssp1_ssm.toml",
            dependencies=["SSP1_SystemStructureCommon"],
            type_prefix="ssm",
        ),
        "ssp2-ssd": SchemaTask(
            standard="SSP2",
            namespace="ssd",
            name="SystemStructureDescription",
            schema_root=repo_root / "3rdParty/SSP2/schema/SystemStructureDescription.xsd",
            output=repo_root / "resources/ssp2_ssd.toml",
            headers=["SSP1_Enums.hpp"],
            dependencies=[
                "SSP2_SystemStructureCommon",
                "SSP2_SystemStructureParameterMapping",
                "SSP2_SystemStructureParameterValues",
            ],
            forward_declarations=["class TSystem;"],
            type_prefix="ssd",
        ),
        "ssp2-ssc": SchemaTask(
            standard="SSP2",
            namespace="ssc",
            name="SystemStructureCommon",
            schema_root=repo_root / "3rdParty/SSP2/schema/SystemStructureCommon.xsd",
            output=repo_root / "resources/ssp2_ssc.toml",
            headers=["SSP1_Enums.hpp"],
            type_prefix="ssc",
        ),
        "ssp2-ssv": SchemaTask(
            standard="SSP2",
            namespace="ssv",
            name="SystemStructureParameterValues",
            schema_root=repo_root / "3rdParty/SSP2/schema/SystemStructureParameterValues.xsd",
            output=repo_root / "resources/ssp2_ssv.toml",
            dependencies=["SSP2_SystemStructureCommon"],
            type_prefix="ssv",
        ),
        "ssp2-ssm": SchemaTask(
            standard="SSP2",
            namespace="ssm",
            name="SystemStructureParameterMapping",
            schema_root=repo_root / "3rdParty/SSP2/schema/SystemStructureParameterMapping.xsd",
            output=repo_root / "resources/ssp2_ssm.toml",
            dependencies=["SSP2_SystemStructureCommon"],
            type_prefix="ssm",
        ),
        "fmi2-md": SchemaTask(
            standard="FMI2",
            namespace="md",
            name="modelDescription",
            schema_root=repo_root / "3rdParty/FMI2/schema/fmi2ModelDescription.xsd",
            output=repo_root / "resources/fmi2_md.toml",
            headers=["FMI2_Enums.hpp"],
            type_prefix="fmi2::md",
        ),
        "fmi3-md": SchemaTask(
            standard="FMI3",
            namespace="md",
            name="fmiModelDescription",
            schema_root=repo_root / "3rdParty/FMI3/schema/fmi3ModelDescription.xsd",
            output=repo_root / "resources/fmi3_md.toml",
            headers=["FMI3_Enums.hpp"],
            type_prefix="fmi3::md",
        ),
    }


def build_task_from_args(args: argparse.Namespace, repo_root: Path) -> SchemaTask:
    presets = load_presets(repo_root)
    if args.preset:
        base = presets[args.preset]
    else:
        base = None

    schema_root = Path(args.xsd_root) if args.xsd_root else (base.schema_root if base else None)
    output = Path(args.output) if args.output else (base.output if base else None)
    standard = args.standard or (base.standard if base else None)
    namespace = args.namespace or (base.namespace if base else None)
    name = args.name or (base.name if base else None)
    headers = args.headers if args.headers is not None else (base.headers if base else [])
    dependencies = (
        args.dependencies
        if args.dependencies is not None
        else (base.dependencies if base else [])
    )
    forward_declarations = (
        args.forward_declarations
        if args.forward_declarations is not None
        else (base.forward_declarations if base else [])
    )
    type_prefix = args.type_prefix or (base.type_prefix if base else namespace)
    root_types = args.root_types or (base.root_types if base else None)

    missing = [
        ("--xsd-root", schema_root),
        ("--output", output),
        ("--standard", standard),
        ("--namespace", namespace),
        ("--name", name),
    ]
    missing_args = [flag for flag, value in missing if value is None]
    if missing_args:
        raise SystemExit(f"Missing required arguments: {', '.join(missing_args)}")

    return SchemaTask(
        standard=standard,  # type: ignore[arg-type]
        namespace=namespace,  # type: ignore[arg-type]
        name=name,  # type: ignore[arg-type]
        schema_root=schema_root,  # type: ignore[arg-type]
        output=output,  # type: ignore[arg-type]
        headers=headers,
        dependencies=dependencies,
        forward_declarations=forward_declarations,
        type_prefix=type_prefix,
        root_types=root_types,
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate TOML schema description files from XSD definitions."
    )
    parser.add_argument(
        "--preset",
        choices=list(load_presets(Path(__file__).resolve().parents[2]).keys()),
        help="Use one of the built in presets for FMI/SSP schemas.",
    )
    parser.add_argument("--xsd-root", help="Path to the root XSD file.")
    parser.add_argument("--output", help="Where to write the generated TOML.")
    parser.add_argument("--standard", help="Value for aaa_standard.")
    parser.add_argument("--namespace", dest="namespace", help="Value for aaa_namespace.")
    parser.add_argument("--name", help="Value for aaa_name.")
    parser.add_argument(
        "--headers",
        nargs="*",
        default=None,
        help="List of header dependencies (aaa_headers).",
    )
    parser.add_argument(
        "--dependencies",
        nargs="*",
        default=None,
        help="List of TOML dependencies (aaa_dependencies).",
    )
    parser.add_argument(
        "--forward-declarations",
        nargs="*",
        default=None,
        help="Forward declarations to add (aaa_forward_declarations).",
    )
    parser.add_argument(
        "--type-prefix",
        help="Prefix prepended to type names when the schema uses unqualified names.",
    )
    parser.add_argument(
        "--root-types",
        nargs="*",
        help="Optional list of root element names to include. Defaults to all root elements in the provided XSD.",
    )
    return parser.parse_args()


def main() -> None:
    repo_root = Path(__file__).resolve().parents[2]
    args = parse_args()
    task = build_task_from_args(args, repo_root)

    parser = XsdParser(task.schema_dir, default_namespace=task.namespace)
    parser.parse()

    roots = task.root_types or root_elements_from_schema(task.schema_root)
    types = reachable_types(parser.types, roots, task.namespace)
    toml = render_toml(task, types)

    task.output.parent.mkdir(parents=True, exist_ok=True)
    task.output.write_text(toml)
    print(f"Wrote {task.output}")


if __name__ == "__main__":
    main()
