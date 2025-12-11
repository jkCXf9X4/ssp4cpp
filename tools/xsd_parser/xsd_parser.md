## Generating TOML from XSD

`xsd_to_toml.py` parses the XSD files under `3rdParty` and emits TOML definitions in the same shape as the files under `resources`.

Preset definitions now live in `tools/xsd_parser/presets.json`. Running the tool with no arguments will load that file and generate TOML for every preset it contains.

- To regenerate everything from the preset file:

```
python3 ./tools/xsd_parser/src/xsd_to_toml.py
```

- To run a specific preset file:

```
python3 ./tools/xsd_parser/src/xsd_to_toml.py --preset-file ./custom_presets.json
```
