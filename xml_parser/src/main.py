

from pathlib import Path
from standard import Standard
from class_exporter import DocumentDeclarationExporter
from xml_exporter import DocumentXmlExporter


def main():

    files = ["xml_parser/resource/ssp1_ssd.toml", "xml_parser/resource/ssp1_ssc.toml", "xml_parser/resource/fmi2_md.toml"]

    lib_path = Path("./lib/schema_parser")

    for f in files:
        t = Standard(f)
        DocumentDeclarationExporter(t).export(lib_path)
        DocumentXmlExporter(t).export(lib_path)
    

if __name__ == "__main__":
    main()