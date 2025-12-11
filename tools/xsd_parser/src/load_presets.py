
import json
from dataclasses import dataclass, field
from pathlib import Path
from typing import Dict, List, Optional



@dataclass
class SchemaTask:
    standard: str
    namespace: str
    name: str
    schema_root: Path
    output: Path
    headers: List[str] = field(default_factory=list)
    dependencies: List[str] = field(default_factory=list)
    forward_declarations: List[str] = field(default_factory=list)
    type_prefix: Optional[str] = None
    root_types: Optional[List[str]] = None

    @property
    def schema_dir(self) -> Path:
        return self.schema_root.parent


def load_presets(repo_root: Path, preset_file: Path) -> Dict[str, SchemaTask]:
    if not preset_file.exists():
        raise SystemExit(f"Preset file not found: {preset_file}")

    try:
        raw_presets = json.loads(preset_file.read_text())
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Failed to parse preset file: {exc}") from exc

    if not isinstance(raw_presets, dict):
        raise SystemExit("Preset file must be a JSON object keyed by preset name.")

    presets: Dict[str, SchemaTask] = {}
    for name, values in raw_presets.items():
        if not isinstance(values, dict):
            raise SystemExit(f"Preset '{name}' must be a JSON object.")
        try:
            schema_root = Path(values["schema_root"])
            output = Path(values["output"])
            namespace = values["namespace"]
            standard = values["standard"]
            task_name = values["name"]
        except KeyError as exc:
            missing = exc.args[0]
            raise SystemExit(f"Preset '{name}' missing required field '{missing}'") from exc

        if not schema_root.is_absolute():
            schema_root = repo_root / schema_root
        if not output.is_absolute():
            output = repo_root / output

        presets[name] = SchemaTask(
            standard=standard,
            namespace=namespace,
            name=task_name,
            schema_root=schema_root,
            output=output,
            headers=list(values.get("headers", [])),
            dependencies=list(values.get("dependencies", [])),
            forward_declarations=list(values.get("forward_declarations", [])),
            type_prefix=values.get("type_prefix", namespace),
            root_types=values.get("root_types"),
        )
    return presets