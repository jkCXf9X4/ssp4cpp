from typing import List
import tomli
from nodes import ClassNode, VariableNode


def indent_strings(indent, string):
    def indent_f(line):
        return f"{indent}{line}"  if line else "" 
    
    return "\n".join([indent_f(line) for line in string.split("\n")])

default_values = {"string": "\"null\"", "int": "0", "float": "0.0", "bool": "false"}

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
                if variable.type == "string":
                    return f"obj.{variable.name}"
                else:
                    return f"to_string(obj.{variable.name} )"

        longest_name = max([len(v.name) for v in self.variable_nodes])

        if variable.list: 
            return f""""{variable.name.ljust(longest_name +3)}: " + to_string_vector(obj.{variable.name.ljust(longest_name + 4) }) + "\\n" +"""

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
string to_string(const optional<{self.class_node.name}> &obj)
{{
    return obj ? to_string(*obj) : "null";
}}

"""
        return template


    def generate_to_string_declarations(self):
        return f"""string to_string(const {self.class_node.name} &obj);
string to_string(const optional<{self.class_node.name}> &obj);
string to_string(const vector<{self.class_node.name}> &obj);
"""

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


def main():
    with open("xml_parser/resource/ssd.toml", "rb") as f:
        ssd_toml = tomli.load(f)
        # print(ssd_toml)

    with open("xml_parser/resource/ssc.toml", "rb") as f:
        ssc_toml = tomli.load(f)
        # print(ssd_toml)

    def get_classes(toml):
        classes = []
        for class_name in toml:
            # print(type)
            t = ClassNode(class_name)
            for variable in toml[class_name]:
                # print(key)
                k = VariableNode(variable, **toml[class_name][variable])
                t.add_child(k)
            classes.append(t)
        return classes



    ssd_classes = [ClassExporter (t) for t in get_classes(ssd_toml)]
    ssc_classes = [ClassExporter (t) for t in get_classes(ssc_toml)]


    def write_to_file(file ,classes, function, mode = "w"):
        with open(file, mode) as f:
            f.write("{")
            for c in classes:
                s = indent_strings("    ", function(c))
                f.write(s)
            f.write("}")

    write_to_file("xml_parser/resource/ssd.hpp", ssd_classes, lambda c: c.generate_class())
    write_to_file("xml_parser/resource/ssc.hpp", ssc_classes, lambda c: c.generate_class())

    # with open("xml_parser/resource/ssd.hpp", "w") as f:
    #     f.write("{")
    #     for c in ssd_classes:
    #         s = indent_strings("    ", c.generate_class())
    #         f.write(s)
    #     f.write("}")



    # with open("xml_parser/resource/ssp_string.hpp", "w") as f:
    #     f.write("{")
    #     for c in classes:
    #         s = indent_strings("    ", c.generate_to_string_declarations())
    #         f.write(s)
    #     f.write("}")

    # with open("xml_parser/resource/ssp_string.cpp", "w") as f:
    #     f.write("{")
    #     for c in ssd_classes:
    #         s = indent_strings("    ", c.generate_class_to_string())
    #         f.write(s)
    #     f.write("}")


main()