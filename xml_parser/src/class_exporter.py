from pathlib import Path
from typing import List

from standard import Node, Attribute, Standard

from misc import indent_strings, new_line


class NodeDeclarationExporter:
    def __init__(self, class_node: Node, indent="    "):
        self.class_node = class_node
        self.variable_nodes: List[Attribute] = class_node.children
        self.indent = indent

    def variable_to_string(self, variable: Attribute):
        longest_name = max([len(v.name) for v in self.variable_nodes])
        return f""""{variable.name.ljust(longest_name +2)}: " + to_str( {variable.name.ljust(longest_name + 1) } ) + "\\n" +"""

    def generate_to_string_definitions(self):
        variables = [
            self.variable_to_string(v)
            for v in self.variable_nodes
            if not v.custom == "function"
        ]
        variables = "\n".join(variables)
        variables = indent_strings("           ", variables)

        template = f""" // {self.class_node.name}
std::string {self.class_node.name}::to_string(void) const
{{
    return "{self.class_node.name} {{ \\n"
{variables}
           "}}";
}}
"""
        return template

    @classmethod
    def generate_variable_declaration(cls, variable: Attribute):
        if variable.list:
            return f"vector<{variable.type}> {variable.name};"
        elif variable.optional:
            return f"optional<{variable.type}> {variable.name};"
        else:
            return f"{variable.type} {variable.name};"

    def generate_class(self):
        variables = [
            self.generate_variable_declaration(v)
            for v in self.variable_nodes
            if not v.custom
        ]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)

        custom_variables = [
            self.generate_variable_declaration(v)
            for v in self.variable_nodes
            if v.custom == "type"
        ]
        custom_variables = "\n".join(custom_variables)
        custom_variables = indent_strings(self.indent, custom_variables)

        custom_functions = [
            v.type for v in self.variable_nodes if v.custom == "function"
        ]
        custom_functions = "\n".join(custom_functions)
        custom_functions = indent_strings(self.indent, custom_functions)

        class_template = f"""
class {self.class_node.name} : public IXmlNode
{{
public:
{variables}

    std::string to_string(void) const;
}};"""
        return class_template


class DocumentDeclarationExporter:
    def __init__(self, standard: Standard, indent="    ") -> None:
        self.standard = standard
        self.indent = indent
        self.nodes = [NodeDeclarationExporter(t) for t in self.standard.classes]

    def get_header_content(self):
        classes = [n.generate_class() for n in self.nodes]
        classes = indent_strings(self.indent, new_line.join(classes))

        headers = new_line.join([f'#include "{h}"' for h in self.standard.headers])
        forward_declarations = new_line.join(
            [f"{self.indent}{d}" for d in self.standard.forward_declarations]
        )

        dependencies = new_line.join(
            [f'#include "{h}.hpp"' for h in self.standard.dependencies]
        )

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename }
#pragma once

#include "IXmlNode.hpp"
{headers}
{dependencies}

#include <string>
#include <vector>
#include <optional>

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace ssp4cpp::interfaces;

{forward_declarations}

{classes}

}}
"""
        return text

    def get_to_string_declaration(self):
        declarations = [n.generate_to_string_definitions() for n in self.nodes]
        declarations = indent_strings(self.indent, new_line.join(declarations))

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename }

#include "{self.standard.long_name}.hpp"
#include "string_conversion.hpp"

#include <string>

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace ssp4cpp::str;

{declarations}
}}
"""
        return text

    def export(self, base_path):
        header_path = (
            base_path
            / "include/schema"
            / self.standard.standard.lower()
            / f"{self.standard.long_name}.hpp"
        )
        to_string_path = (
            base_path
            / "src/schema"
            / self.standard.standard.lower()
            / f"{self.standard.long_name}_String.cpp"
        )

        print(header_path)
        print(to_string_path)

        with open(header_path, "w") as f:
            f.write(self.get_header_content())

        with open(to_string_path, "w") as f:
            f.write(self.get_to_string_declaration())
