from pathlib import Path
from typing import List
from standard import Node, Attribute, Standard

from misc import indent_strings, new_line

default_values = {
    "string": '"null"',
    "int": "0",
    "unsigned int": "0",
    "double": "0.0",
    "bool": "false",
}


class NodeXmlExporter:
    def __init__(self, class_node: Node, indent="    "):
        self.class_node = class_node
        self.variable_nodes: List[Attribute] = class_node.children
        self.indent = indent

        self.longest_name = max(
            [
                0,
            ]
            + [len(v.name) for v in self.variable_nodes]
        )

    def generate_from_xml_declarations(self):
        return (
            f"""void from_xml(const xml_node &node, {self.class_node.name } &obj);\n"""
        )

    def generate_variable_declaration(self, variable: Attribute):
        if variable.xml_tag:
            name = (
                variable.xml_tag
                if not variable.namespace
                else f"{variable.namespace}:{variable.xml_tag}"
            )
        else:
            name = (
                variable.name
                if not variable.namespace
                else f"{variable.namespace}:{variable.name}"
            )

        return f'ssp4cpp::common::xml::parse_xml(node, obj.{variable.name.ljust(self.longest_name +2)}, "{name}");'

    def generate_parser(self):
        variables = [
            self.generate_variable_declaration(v)
            for v in self.variable_nodes
        ]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)

    
        experimental_nodes = [v.name for v in self.variable_nodes if v.experimental]
        warning_text = ""
        if experimental_nodes:
            warning_text = f"log.warning(\"Experimental feature {','.join(experimental_nodes)} used\");\n"

        template = f"""
void from_xml(const xml_node &node, {self.class_node.name} &obj)
{{
    log.ext_trace("Parsing {self.class_node.name}");
    {warning_text}
{variables}

    log.ext_trace("Completed {self.class_node.name}");
}}
"""
        return template


class DocumentXmlExporter:
    def __init__(self, standard: Standard, indent="    ") -> None:
        self.standard = standard
        self.indent = indent
        self.nodes = [NodeXmlExporter(t) for t in self.standard.classes]

    def get_parser_declaration(self):
        decs = [n.generate_from_xml_declarations() for n in self.nodes]
        decs = indent_strings(self.indent, new_line.join(decs))

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename }

#pragma once

#include "{self.standard.long_name}.hpp"
#include <pugixml.hpp>

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace pugi;

{decs}

}}
"""
        return text

    def get_parsers_definitions(self):
        parsers = [n.generate_parser() for n in self.nodes]
        parsers = indent_strings(self.indent, new_line.join(parsers))

        dependencies = new_line.join(
            [f'#include "{h}_XML.hpp"' for h in self.standard.dependencies]
        )

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename}

#include "{self.standard.long_name}_XML.hpp"
{dependencies}

#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace pugi;
{self.indent}using namespace common;

{self.indent}auto log = Logger("{self.standard.long_namespece.replace('::', '.')}", LogLevel::info);

{parsers}
}}
"""
        return text

    def export(self, base_path):
        xml_declaration_path = (
            base_path
            / "include_private"
            / self.standard.standard.lower()
            / f"{self.standard.long_name}_XML.hpp"
        )
        xml_definition_path = (
            base_path
            / "src/schema"
            / self.standard.standard.lower()
            / f"{self.standard.long_name}_XML.cpp"
        )

        print(xml_declaration_path)
        print(xml_definition_path)

        with open(xml_declaration_path, "w") as f:
            f.write(self.get_parser_declaration())

        with open(xml_definition_path, "w") as f:
            f.write(self.get_parsers_definitions())
