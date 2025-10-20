

from pathlib import Path
from standard import Standard
from class_exporter import DocumentDeclarationExporter
from xml_exporter import DocumentXmlExporter


def main():

    files = ["resource/ssp1_ssd.toml", 
             "resource/ssp1_ssc.toml", 
             "resource/ssp1_ssv.toml", 
             "resource/ssp1_ssm.toml", 
             "resource/fmi2_md.toml",
             ]

    lib_path = Path("./lib/schema")

    for f in files:
        t = Standard(f)
        DocumentDeclarationExporter(t).export(lib_path)
        DocumentXmlExporter(t).export(lib_path)
    

if __name__ == "__main__":
    main()