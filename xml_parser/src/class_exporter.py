from typing import List
import tomli
from nodes import ClassNode, VariableNode

from misc import indent_strings

default_values = {"string": "\"null\"", "int": "0", "unsigned int": "0", "double": "0.0", "bool": "false"}

class ClassExporter:

    def __init__(self, class_node : ClassNode, indent="    "):
        self.class_node = class_node
        self.variable_nodes : List[VariableNode] = class_node.children
        self.indent = indent

    def variable_to_string(self, variable : VariableNode):

        def get_right_side():
            if variable.optional:
                if variable.is_primitive:
                    if variable.type == "string":
                        return f"obj.{variable.name}.value_or({default_values[variable.type]})"
                    else:
                        return f"std::to_string( obj.{variable.name}.value_or({default_values[variable.type]}) )"
                else: # complex type
                    return f"to_string( obj.{variable.name} )"
            else: 
                if variable.is_primitive:
                    if variable.type == "string":
                        return f"obj.{variable.name}"
                    else:
                        return f"std::to_string( obj.{variable.name} )"
                else:
                    return f"to_string( obj.{variable.name} )"

        longest_name = max([len(v.name) for v in self.variable_nodes])

        if variable.list: 
            return f""""{variable.name.ljust(longest_name +3)}: " + to_string(obj.{variable.name.ljust(longest_name + 4) }) + "\\n" +"""
        else:
            return f""""{variable.name.ljust(longest_name +3)}: " + {get_right_side().ljust(longest_name + 40 )} + "\\n" +"""

    def generate_class_to_string(self):
        variables = [self.variable_to_string(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings("           ", variables)

        template = f""" // {self.class_node.name}
string to_string(const {self.class_node.name} &obj)
{{
    return "{self.class_node.name} {{ \\n"
{variables}
           "}}";
}}
string to_string(const optional<{self.class_node.name}> &obj) {{ return to_string_optional(obj); }}
string to_string(const vector<{self.class_node.name}> &obj) {{ return to_string_vector(obj); }}

"""
        return template


    def generate_to_string_declarations(self):
        return f"""string to_string(const {self.class_node.name} &obj);
string to_string(const optional<{self.class_node.name}> &obj);
string to_string(const vector<{self.class_node.name}> &obj);
"""

    def generate_from_xml_declarations(self):
        return f"""void from_xml(const xml_node &node, {self.class_node.name } &obj);\n"""

    @classmethod
    def generate_variable_declaration(cls, variable : VariableNode):
        if variable.list:
            return f"vector<{variable.type}> {variable.name};"
        elif variable.optional:
            return f"optional<{variable.type}> {variable.name};"
        else:
            return f"{variable.type} {variable.name};"

    def generate_class(self):
        variables = [self.generate_variable_declaration(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)
            

        class_template = f"""
class {self.class_node.name}
{{
public:
{variables}
}};
{self.generate_to_string_declarations()}"""
        return class_template
