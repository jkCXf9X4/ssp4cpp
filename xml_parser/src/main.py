from typing import List
import tomli
from nodes import ClassNode, VariableNode


def indent_strings(indent, string):
    return "\n".join([f"{indent}{line}" for line in string.split("\n")])


default_values = {"string": "null", "int": "0", "float": "0.0", "bool": "false"}




class ClassExporter:

    def __init__(self, class_node : ClassNode, indent="    "):
        self.class_node = class_node
        self.variable_nodes : List[VariableNode] = class_node.children
        self.indent = indent

    def variable_to_string(self, variable : VariableNode):

        def get_right_side():
            if variable.optional:
                if variable.is_primitive:
                    return f"to_string(          obj.{variable.name}.value_or({default_values[variable.type]}) )"
                else: # complex type
                    return f"to_string_optional( obj.{variable.name} )"
            else: 
                return f"to_string(          obj.{variable.name}) )"

        longest_name = max([len(v.name) for v in self.variable_nodes])

        if variable.list: 
            return f""" {variable.name.ljust(longest_name +3)}: " + to_string_vector(obj.{variable.name.ljust(longest_name + 4) }) + "\\n" +"""

        else:
            return f""""{variable.name.ljust(longest_name +3)}: " + {get_right_side().ljust(longest_name + 40 )} + "\\n" +"""

    def generate_class_to_string(self):
        variables = [self.variable_to_string(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings("           ", variables)

        template = f"""string to_string(const {self.class_node.name} &obj)
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
            return f"vector<{variable.type}> {variable.name}"
        elif variable.optional:
            return f"optional<{variable.type}> {variable.name}"
        else:
            return f"{variable.type} {variable.name}"

    def generate_class(self):
        variables = [self.generate_variable_declaration(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)
            

        class_template = f"""class {self.class_node.name}
{{
public:
{variables}

string to_string()
}};
string to_string(const {self.class_node.name} &obj);
"""
        return class_template


def main():
    with open("xml_parser/resource/test.toml", "rb") as f:
        parsed_toml = tomli.load(f)
        print(parsed_toml)

    types = []
    for type in parsed_toml:
        # print(type)
        t = ClassNode(type)
        for key in parsed_toml[type]:
            # print(key)
            k = VariableNode(key, **parsed_toml[type][key])
            t.add_child(k)
        types.append(t)


    classes = [ClassExporter (t) for t in types]

    for c in classes:
        print(c.generate_class())

    for c in classes:
        print(c.generate_class_to_string())


main()