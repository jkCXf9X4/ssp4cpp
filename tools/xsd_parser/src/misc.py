from __future__ import annotations

from dataclasses import dataclass, field, replace
from typing import List, Optional, Tuple

import xml.etree.ElementTree as ET

from pathlib import Path


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


def type_is_primitive(type_name: str) -> bool:
    return type_name in PRIMITIVE_TYPES.values()


def root_elements_from_schema(schema: Path) -> List[str]:
    tree = ET.parse(schema)
    root = tree.getroot()
    return [
        el.attrib["name"]
        for el in root.findall("xs:element", NS)
        if "name" in el.attrib
    ]


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
