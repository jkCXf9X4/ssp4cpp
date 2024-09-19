
import tomli
from nodes import ClassNode, VariableNode
from class_exporter import ClassExporter

from misc import indent_strings


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
            f.write("{\n")
            for c in classes:
                s = indent_strings("    ", function(c))
                f.write(s)
            f.write("\n}\n")

    write_to_file("xml_parser/generated/ssd.hpp", ssd_classes, lambda c: c.generate_class())
    write_to_file("xml_parser/generated/ssc.hpp", ssc_classes, lambda c: c.generate_class())

    write_to_file("xml_parser/generated/ssd_string.cpp", ssd_classes, lambda c: c.generate_class_to_string())
    write_to_file("xml_parser/generated/ssc_string.cpp", ssc_classes, lambda c: c.generate_class_to_string())

    write_to_file("xml_parser/generated/ssd_xml.cpp", ssd_classes, lambda c: c.generate_from_xml_declarations())
    write_to_file("xml_parser/generated/ssc_xml.cpp", ssc_classes, lambda c: c.generate_from_xml_declarations())

main()