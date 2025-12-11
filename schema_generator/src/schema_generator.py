from pathlib import Path
from standard import Standard
from class_exporter import DocumentDeclarationExporter
from xml_exporter import DocumentXmlExporter


def main():
    files = [
        "./resources/ssp1_ssd.toml",
        "./resources/ssp1_ssc.toml",
        "./resources/ssp1_ssv.toml",
        "./resources/ssp1_ssm.toml",
        "./resources/fmi2_md.toml",
    ]

    lib_path = Path("./lib/").resolve()

    print(f"Lib path {lib_path}")

    for f in files:
        t = Standard(f)
        DocumentDeclarationExporter(t).export(lib_path)
        DocumentXmlExporter(t).export(lib_path)


if __name__ == "__main__":
    main()
