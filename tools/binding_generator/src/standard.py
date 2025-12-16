from pathlib import Path
import tomli


class ABC_Node:
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


class Node(ABC_Node):
    def __init__(self, name: str):
        super().__init__(name)
        self.is_enum = False

    def __str__(self):
        return f"Node: name={self.name}, children={self.children}, is_enum={self.is_enum}"


class Attribute(ABC_Node):
    default_values = {
        "string": '"null"',
        "int": "0",
        "unsigned int": "0",
        "double": "0.0",
        "bool": "false",
    }
    primitives = list(default_values.keys())

    def __init__(
        self,
        name,
        type="string",
        optional=False,
        list=False,
        enum_val= None,
        is_enum=None,
        delimitation=None,
        namespace=None,
        xml_tag=None,
        experimental=None, # Non std complient, will warn during parsing if these are used
    ):
        super().__init__(name)
        self.type = type
        self.optional = optional
        self.list = list
        self.namespace = namespace
        self.xml_tag = xml_tag
        self.experimental = experimental
        self.enum_value = enum_val
        self.delimitation = delimitation
        self.is_enum = is_enum

        self.is_primitive = type in self.primitives

    def __str__(self):
        return f"{self.name} ({self.type}, optional={self.optional}, list={self.list}, namespace={self.namespace}, xml_tag={self.xml_tag}, experimental={self.experimental}, enum_val={self.enum_value}, is_enum={self.is_enum}, delimitation='{self.delimitation}')"


class Standard:
    def __init__(self, file) -> None:
        with open(file, "rb") as f:
            self.toml = tomli.load(f)
        self.filename = Path(file).name
        self.name = ""
        self.headers = []
        self.forward_declarations = []
        self.namespace = ""
        self.standard = ""
        self.dependencies = []

        self.classes = self.get_classes()

        self.long_namespece = "::".join(["ssp4cpp", self.standard.lower(), self.namespace.lower()])
        self.long_name = f"{self.standard}_{self.name}"

        print(f"{self.name=} {self.headers=} {self.forward_declarations=}")


    def get_classes(self) -> list[Node]:
        classes = []
        for name in self.toml:
            if name == "aaa_name":
                self.name = self.toml[name]
            elif name == "aaa_headers":
                self.headers = self.toml[name]
            elif name == "aaa_forward_declarations":
                self.forward_declarations = self.toml[name]
            elif name == "aaa_namespace":
                self.namespace = self.toml[name]
            elif name == "aaa_standard":
                self.standard = self.toml[name]
            elif name == "aaa_dependencies":
                self.dependencies = self.toml[name]

            else:
                print(name)
                node = Node(name)
                for variable in self.toml[name]:
                    print(variable)
                    attrib = Attribute(variable, **self.toml[name][variable])

                    node.add_child(attrib)
                    # If one of the attributes is an enum_value then the type is an enum
                    node.is_enum = node.is_enum or attrib.enum_value is not None
                classes.append(node)
        return classes
