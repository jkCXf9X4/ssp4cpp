

from standard import Standard
from class_exporter import DocumentDeclarationExporter
from xml_exporter import DocumentXmlExporter
# from xml_parser.src.toml_parser import ClassNode, VariableNode
# from xml_parser_exporter import XmlParserExporter



def main():

    files = ["xml_parser/resource/ssp1_ssd.toml", "xml_parser/resource/ssp1_ssc.toml", "xml_parser/resource/fmi2_md.toml"]

    for f in files:
        t = Standard(f)
        DocumentDeclarationExporter(t).export()
        DocumentXmlExporter(t).export()
    

if __name__ == "__main__":
    main()