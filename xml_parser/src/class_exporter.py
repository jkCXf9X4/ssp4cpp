from typing import List
import tomli
from nodes import ClassNode, VariableNode

from misc import indent_strings, new_line



class ClassExporter:

    def __init__(self, class_node : ClassNode, indent="    "):
        self.class_node = class_node
        self.variable_nodes : List[VariableNode] = class_node.children
        self.indent = indent

    def variable_to_string(self, variable : VariableNode):
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
    def generate_variable_declaration(cls, variable : VariableNode):
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
{"    // Custom variables" + new_line if custom_variables else ""}{custom_variables}
{"    // Custom Functions" + new_line if custom_functions else ""}{custom_functions}
}};

"""
        return class_template
