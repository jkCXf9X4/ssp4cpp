from __future__ import annotations

from typing import Dict, Iterable, List, Optional, Tuple

from misc import TypeDefinition, format_type_name, type_is_primitive

from load_presets import SchemaTask


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



