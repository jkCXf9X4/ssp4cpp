from pathlib import Path
from typing import List

from standard import Node, Attribute, Standard

from misc import indent_strings, new_line, format_schema_include, join_indent



class NodeDeclarationExporter:
    def __init__(self, class_node: Node, indent="    "):
        self.class_node = class_node
        self.variable_nodes: List[Attribute] = class_node.children
        self.is_enum = class_node.is_enum
        self.indent = indent

    def variable_to_string(self, variable: Attribute):
        longest_name = max([len(v.name) for v in self.variable_nodes])
        return f""""{variable.name.ljust(longest_name + 2)}: " + to_str( {variable.name.ljust(longest_name + 1)} ) + "\\n" +"""

    def generate_to_string_definitions(self):
        variables = [self.variable_to_string(v) for v in self.variable_nodes]
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
        t = "std::string" if variable.type == "string" else variable.type
        if variable.list:
            return f"std::vector<{t}> {variable.name};"
        elif variable.optional:
            return f"std::optional<{t}> {variable.name};"
        else:
            return f"{t} {variable.name};"

    def generate_class(self):
        variables = [self.generate_variable_declaration(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)

        class_template = f"""
class {self.class_node.name} : public IXmlNode
{{
public:
{variables}

    std::string to_string(void) const;
}};"""
        return class_template
    
    def generate_enum(self):
        variables = [f"{v.name}, // {v.enum_value}" for v in self.variable_nodes]
        variables = join_indent(variables, "        ")

        to_str_def = [f"case Value::{v.name}: return \"{v.enum_value}\";" for v in self.variable_nodes]
        to_str_def = join_indent(to_str_def, "        ")

        from_str_def = [f"if (str == \"{v.enum_value}\") value = Value::{v.name};" for v in self.variable_nodes]
        if len(from_str_def) > 1:
            from_str_def = [from_str_def[0]] + ["else " + s for s in from_str_def[1:]]
        from_str_def = join_indent(from_str_def, "        ")

        enum_template = f"""
class {self.class_node.name} : public IEnum
{{
public:
    enum Value:int
    {{
{variables}
        unknown, // unknown
    }};

    {self.class_node.name}() = default;
    constexpr {self.class_node.name}(Value value) : value(value) {{}}
    operator Value () const {{return value;}}

    std::string to_string() const override
    {{
        switch (value)
        {{
{to_str_def}
        default:
            return "unknown";
        }}
    }}

    void from_string(const std::string &str) override
    {{
{from_str_def}
        else
        {{
            value = Value::unknown;
        }}
    }}
    private:
        Value value{{Value::unknown}};
}};"""
        return enum_template


class DocumentDeclarationExporter:
    def __init__(self, standard: Standard, indent="    ") -> None:
        self.standard = standard
        self.indent = indent
        self.nodes = [NodeDeclarationExporter(t) for t in self.standard.classes]

    def get_header_content(self):
        classes = [n.generate_class() for n in self.nodes if not n.is_enum]
        classes = indent_strings(self.indent, new_line.join(classes))

        enums = [n.generate_enum() for n in self.nodes if n.is_enum]
        enums = indent_strings(self.indent, new_line.join(enums))

        headers = new_line.join(
            [
                f'#include "{format_schema_include(h)}"'
                for h in self.standard.headers
            ]
        )
        forward_declarations = new_line.join(
            [f"{self.indent}{d}" for d in self.standard.forward_declarations]
        )

        dependencies = new_line.join(
            [
                f'#include "{format_schema_include(h)}.hpp"'
                for h in self.standard.dependencies
            ]
        )

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename}
#pragma once

#include "ssp4cpp/utils/interface.hpp"
#include "ssp4cpp/utils/xml.hpp"

{headers}
{dependencies}

#include <string>
#include <vector>
#include <optional>

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace utils::interfaces;
{self.indent}using namespace utils::xml;

{forward_declarations}

{enums}

{classes}

}}
"""
        return text

    def get_to_string_declaration(self):
        declarations = [n.generate_to_string_definitions() for n in self.nodes if not n.is_enum]
        declarations = indent_strings(self.indent, new_line.join(declarations))

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename}

#include "ssp4cpp/schema/{self.standard.standard.lower()}/{self.standard.long_name}.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace {self.standard.long_namespece}
{{
{self.indent}using namespace utils::str;


{declarations}
}}
"""
        return text

    def export(self, base_path):
        header_path = (
            base_path
            / "include"
            / "ssp4cpp"
            / "schema"
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
