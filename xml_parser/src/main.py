
import tomli
from nodes import ClassNode, VariableNode
from class_exporter import ClassExporter

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

    def parse_toml(file):
        with open(file, "rb") as f:
            toml = tomli.load(f)
            classes = [ClassExporter (t) for t in get_classes(toml)]
        return classes
    

    ssd_classes = parse_toml("xml_parser/resource/ssd.toml")
    ssc_classes = parse_toml("xml_parser/resource/ssc.toml")
    fmi2_md_classes = parse_toml("xml_parser/resource/fmi2_modelDescription.toml")


    write_to_file("xml_parser/generated/ssd.hpp", ssd_classes, lambda c: c.generate_class())
    write_to_file("xml_parser/generated/ssd_string.cpp", ssd_classes, lambda c: c.generate_class_to_string())
    write_to_file("xml_parser/generated/ssd_xml.cpp", ssd_classes, lambda c: c.generate_from_xml_declarations())

    write_to_file("xml_parser/generated/ssc.hpp", ssc_classes, lambda c: c.generate_class())
    write_to_file("xml_parser/generated/ssc_string.cpp", ssc_classes, lambda c: c.generate_class_to_string())
    write_to_file("xml_parser/generated/ssc_xml.cpp", ssc_classes, lambda c: c.generate_from_xml_declarations())

    write_to_file("xml_parser/generated/fmi2_md.hpp", fmi2_md_classes, lambda c: c.generate_class())
    write_to_file("xml_parser/generated/fmi2_md_string.cpp", fmi2_md_classes, lambda c: c.generate_class_to_string())
    write_to_file("xml_parser/generated/fmi2_md_xml.cpp", fmi2_md_classes, lambda c: c.generate_from_xml_declarations())




main()