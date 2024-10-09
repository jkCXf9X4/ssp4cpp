from pathlib import Path
from typing import List

from toml_parser import Node, Attribute, Standard

from misc import indent_strings, new_line



class NodeExporter:

    def __init__(self, class_node : Node, indent="    "):
        self.class_node = class_node
        self.variable_nodes : List[Attribute] = class_node.children
        self.indent = indent

    def variable_to_string(self, variable : Attribute):
        longest_name = max([len(v.name) for v in self.variable_nodes])
        return f""""{variable.name.ljust(longest_name +2)}: " + to_str( {variable.name.ljust(longest_name + 1) } ) + "\\n" +"""

    def generate_to_string_definitions(self):
        variables = [self.variable_to_string(v) for v in self.variable_nodes if not v.custom == "function"] 
        variables = "\n".join(variables)
        variables = indent_strings("           ", variables)

        template = f""" // {self.class_node.name}
string {self.class_node.name}::to_string(void) const
{{
    return "{self.class_node.name} {{ \\n"
{variables}
           "}}";
}}

"""
        return template

    @classmethod
    def generate_variable_declaration(cls, variable : Attribute):
        if variable.list:
            return f"vector<{variable.type}> {variable.name};"
        elif variable.optional:
            return f"optional<{variable.type}> {variable.name};"
        else:
            return f"{variable.type} {variable.name};"

    def generate_class(self):
        variables = [self.generate_variable_declaration(v) for v in self.variable_nodes if not v.custom]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)

        custom_variables = [self.generate_variable_declaration(v) for v in self.variable_nodes if v.custom == "type"]
        custom_variables = "\n".join(custom_variables)
        custom_variables = indent_strings(self.indent, custom_variables)

        custom_functions = [v.type for v in self.variable_nodes if v.custom == "function"]
        custom_functions = "\n".join(custom_functions)
        custom_functions = indent_strings(self.indent, custom_functions)
            

        class_template = f"""
class {self.class_node.name} : public IXmlNode
{{
public:
{variables}

    string to_string(void) const;
}};"""
        return class_template


class ClassExporter:

    def __init__(self, standard : Standard, indent="    ") -> None:
        self.standard = standard
        self.indent = indent

    
    def get_header_content(self):
        nodes = [NodeExporter (t) for t in self.standard.classes]

        classes = [n.generate_class() for n in nodes]
        classes = indent_strings(self.indent, new_line.join(classes)) 
        
        headers = new_line.join([f"#include \"{h}\"" for h in self.standard.headers])
        forward_declarations = new_line.join([f"{self.indent}{d}" for d in self.standard.forward_declarations])

        text = f"""

// This is a generated file, do not alter
// it is based on {self.standard.filename }

#include "IXmlNode.hpp"
{headers}

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

    
    def export(self):
        header_path = Path("./include/schema") / self.standard.standard.lower() / (self.standard.name + ".hpp")
        to_string_path = Path("./src/schema") / self.standard.standard.lower() / (self.standard.name + "_String.cpp")

        print(header_path)
        print(to_string_path)

        with open(header_path, "w") as f:
            f.write(self.get_header_content())


    # def export(file, prefix):
    #     with open(file, "rb") as f:
            

    
    #         
    #         xml_parsers_exporters = [XmlParserExporter (t) for t in get_classes(toml)]

    #     write_to_file(f"xml_parser/generated/{prefix}_class.hpp", class_exporters, lambda c: c.generate_class())
    #     write_to_file(f"xml_parser/generated/{prefix}_class_string.cpp", class_exporters, lambda c: c.generate_to_string_definitions())
