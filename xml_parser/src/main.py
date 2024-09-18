from typing import List
import tomli
from nodes import ClassNode, VariableNode


def indent_strings(indent, string):
    return "\n".join([f"{indent}{line}" for line in string.split("\n")])


class Class:

    def __init__(self, class_node : ClassNode):
        self.class_node = class_node
        self.variable_nodes : List[VariableNode] = class_node.children

    @classmethod
    def variable_to_string(cls, variable : VariableNode):
        if variable.list:
            return f"\"{variable.name}: \" + to_string({variable.name})"
        elif variable.optional:
            return f"\"{variable.name}: \" + {variable.name}.value_or(\"null\")"
        else:
            return f"\"{variable.name}: \" + {variable.name}"

    def generate_class_to_string(self):
        out = ""

        """
    string to_string(const Connection &obj)
    {
        return "Connection {\n" 
               "startElement: " + conn.startElement.value_or("null") + "\n" +
               "startConnector: " + conn.startConnector + "\n" +
               "endElement: " + conn.endElement.value_or("null") + "\n" +
               "endConnector: " + conn.endConnector + "\n" +
               "suppressUnitConversion: " + std::to_string(conn.suppressUnitConversion.value_or(false)) +
               "LinearTransformation: " + to_string_optional(conn.LinearTransformation) +
               "BooleanMappingTransformation: " + to_string_optional(conn.BooleanMappingTransformation) +
               "IntegerMappingTransformation: " + to_string_optional(conn.IntegerMappingTransformation) +
               "EnumerationMappingTransformation: " + to_string_optional(conn.EnumerationMappingTransformation) +
               "ConnectionGeometry: " + to_string_optional(conn.ConnectionGeometry) +
               "Annotations: " + to_string_optional(conn.Annotations) +
               " }";
    }
        """


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
        variables = indent_strings("    ", variables)
            

        class_template = f"""class {self.class_node.name}
{{
public:
{variables}

string to_string()
}};
string to_string(const {self.class_node.name} &obj);
"""
        print(class_template)


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


    for t in types:
        Class.generate_class(t)


main()