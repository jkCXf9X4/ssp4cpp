
import tomli
from nodes import ClassNode, VariableNode
from class_exporter import ClassExporter
from xml_parser_exporter import XmlParserExporter

from misc import indent_strings


def main():

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

    def write_to_file(file ,classes, function, mode = "w"):
        with open(file, mode) as f:
            f.write("{\n")
            for c in classes:
                s = indent_strings("    ", function(c))
                f.write(s)
            f.write("\n}\n")


    def export(file, prefix):
        with open(file, "rb") as f:
            toml = tomli.load(f)
            class_exporters = [ClassExporter (t) for t in get_classes(toml)]
            xml_parsers_exporters = [XmlParserExporter (t) for t in get_classes(toml)]

        write_to_file(f"xml_parser/generated/{prefix}_class.hpp", class_exporters, lambda c: c.generate_class())
        write_to_file(f"xml_parser/generated/{prefix}_class_string.cpp", class_exporters, lambda c: c.generate_to_string_definitions())

        write_to_file(f"xml_parser/generated/{prefix}_xml_parser.hpp", xml_parsers_exporters, lambda c: c.generate_from_xml_declarations())
        write_to_file(f"xml_parser/generated/{prefix}_xml_parser.cpp", xml_parsers_exporters, lambda c: c.generate_parsers())


    export("xml_parser/resource/ssd.toml", "ssd")
    export("xml_parser/resource/ssc.toml", "ssc")
    export("xml_parser/resource/fmi2_modelDescription.toml", "fmi2_md")

if __name__ == "__main__":
    main()