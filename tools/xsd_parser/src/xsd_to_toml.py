from __future__ import annotations

import argparse
from pathlib import Path
from typing import List

from load_presets import SchemaTask, load_presets

from misc import root_elements_from_schema

from xsd_parser import XsdParser
from export_toml import reachable_types, render_toml



def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Generate TOML schema description files from XSD definitions."
    )
    parser.add_argument(
        "--preset-file",
        help="Path to a JSON file that defines presets. Defaults to tools/xsd_parser/presets.json.",
        default="./resources/presets.json"
    )
    return parser.parse_args()


def main() -> None:
    repo_root = Path(__file__).resolve().parents[3]
    args = parse_args()

    preset_file = Path(args.preset_file)
    print(f"Loading preset file: {preset_file}")
    
    tasks = load_presets(repo_root, preset_file)

    for name, task in tasks.items() :
        parser = XsdParser(task.schema_dir, default_namespace=task.namespace)
        parser.parse()

        roots = task.root_types or root_elements_from_schema(task.schema_root)
        if not roots:
            roots = [
                name for (ns, name) in parser.types.keys() if ns == task.namespace
            ]
        types = reachable_types(parser.types, roots, task.namespace)
        toml = render_toml(task, types)

        task.output.parent.mkdir(parents=True, exist_ok=True)
        task.output.write_text(toml)
        print(f"Wrote {task.output}")


if __name__ == "__main__":
    main()
