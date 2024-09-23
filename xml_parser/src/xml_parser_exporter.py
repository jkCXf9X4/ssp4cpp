from typing import List
from nodes import ClassNode, VariableNode

from misc import indent_strings

default_values = {"string": "\"null\"", "int": "0", "unsigned int": "0", "double": "0.0", "bool": "false"}

class XmlParserExporter:

    def __init__(self, class_node : ClassNode, indent="    "):
        self.class_node = class_node
        self.variable_nodes : List[VariableNode] = class_node.children
        self.indent = indent

        self.longest_name = max([0,] +[len(v.name) for v in self.variable_nodes])

    def generate_from_xml_declarations(self):
        return f"""void from_xml(const xml_node &node, {self.class_node.name } &obj);\n"""

    def generate_variable_declaration(self, variable : VariableNode):

        if variable.xml_tag:
            name = variable.xml_tag if not variable.namespace else f"{variable.namespace}:{variable.xml_tag}"
        else:
            name = variable.name if not variable.namespace else f"{variable.namespace}:{variable.name}"

        return f"parse_xml(node, obj.{variable.name.ljust(self.longest_name +2)}, \"{name}\");"

    def generate_parsers(self):
        variables = [self.generate_variable_declaration(v) for v in self.variable_nodes]
        variables = "\n".join(variables)
        variables = indent_strings(self.indent, variables)
            

        template = f"""
void from_xml(const xml_node &node, {self.class_node.name} &obj)
{{
    BOOST_LOG_TRIVIAL(trace) << "Parsing {self.class_node.name}" << std::endl;

{variables}

    BOOST_LOG_TRIVIAL(trace) << "Completed {self.class_node.name}" << std::endl;
}}
"""
        return template
