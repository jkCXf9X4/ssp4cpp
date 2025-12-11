from pathlib import Path
from standard import Standard
from class_exporter import DocumentDeclarationExporter
from xml_exporter import DocumentXmlExporter


def main():
    files = [
        # "./resources/ssp1/ssp1_ssd.toml",
        # "./resources/ssp1/ssp1_ssc.toml",
        # "./resources/ssp1/ssp1_ssv.toml",
        # "./resources/ssp1/ssp1_ssm.toml",
        "./resources/ssp1/ssp1_enums.toml",
        # "./resources/fmi2/fmi2_md.toml",
        "./resources/fmi2/fmi2_enums.toml",
    ]

    lib_path = Path("./lib/").resolve()

    print(f"Lib path {lib_path}")

    for f in files:
        standard = Standard(f)

        for cls in standard.classes:
            cls.print_tree()

        DocumentDeclarationExporter(standard).export(lib_path)
        DocumentXmlExporter(standard).export(lib_path)


if __name__ == "__main__":
    main()
