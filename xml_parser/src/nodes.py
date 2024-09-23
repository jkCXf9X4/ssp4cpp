
class Node:
    def __init__(self, name):
        self.name = name
        self.children = []

    def add_child(self, child):
        self.children.append(child)

    def __str__(self):
        return f"{self.name}"
    
    def print_tree(self, level=0):
        print("  " * level + str(self))
        for child in self.children:
            child.print_tree(level + 1)

class ClassNode(Node):
    
    def __init__(self, name):
        super().__init__(name)

class VariableNode(Node):

    default_values = {"string": "\"null\"", "int": "0", "unsigned int": "0", "double": "0.0", "bool": "false"}
    primitives = list(default_values.keys())

    def __init__(self, name, type = "string", optional=False, list=False, namespace=None, xml_tag=None):
        super().__init__(name)
        self.type = type
        self.optional = optional
        self.list = list
        self.namespace = namespace
        self.xml_tag = xml_tag
        self.is_primitive = type in self.primitives

    def __str__(self):
        return f"{self.name} ({self.type}, optional={self.optional}, list={self.list})"
