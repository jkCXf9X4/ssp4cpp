

from toml_parser import Standard
from class_exporter import ClassExporter
# from xml_parser.src.toml_parser import ClassNode, VariableNode
# from xml_parser_exporter import XmlParserExporter



def main():

    files = ["xml_parser/resource/ssp1_ssd.toml", "xml_parser/resource/ssp1_ssc.toml", "xml_parser/resource/fmi2_modelDescription.toml"]
    # standards = [Standard(file) for file in files]


    t = Standard(files[0])
    
    ClassExporter(t).export()

    # def write_to_file(file ,classes, function, mode = "w"):
    #     with open(file, mode) as f:
    #         f.write("{\n")
    #         for c in classes:
    #             s = indent_strings("    ", function(c))
    #             f.write(s)
    #         f.write("\n}\n")


    # def export(file, prefix):
    #     with open(file, "rb") as f:
            

    
    #         class_exporters = [ClassExporter (t) for t in get_classes(toml)]
    #         xml_parsers_exporters = [XmlParserExporter (t) for t in get_classes(toml)]

    #     write_to_file(f"xml_parser/generated/{prefix}_class.hpp", class_exporters, lambda c: c.generate_class())
    #     write_to_file(f"xml_parser/generated/{prefix}_class_string.cpp", class_exporters, lambda c: c.generate_to_string_definitions())

    #     write_to_file(f"xml_parser/generated/{prefix}_xml_parser.hpp", xml_parsers_exporters, lambda c: c.generate_from_xml_declarations())
    #     write_to_file(f"xml_parser/generated/{prefix}_xml_parser.cpp", xml_parsers_exporters, lambda c: c.generate_parsers())


    # export("xml_parser/resource/ssd.toml", "ssd")
    # export("xml_parser/resource/ssc.toml", "ssc")
    # export("xml_parser/resource/fmi2_modelDescription.toml", "fmi2_md")

if __name__ == "__main__":
    main()