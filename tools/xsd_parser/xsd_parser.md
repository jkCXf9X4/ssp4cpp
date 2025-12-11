## Generating TOML from XSD

`xsd_to_toml.py` parses the XSD files under `3rdParty` and emits TOML definitions in the same shape as the files under `resources`.

Presets exist for the current standards:

- `ssp1-ssd`, `ssp1-ssc`, `ssp1-ssv`, `ssp1-ssm`
- `ssp2-ssd`, `ssp2-ssc`, `ssp2-ssv`, `ssp2-ssm`
- `fmi2-md`, `fmi3-md`

Example:

```
python3 ./tools/xsd_parser/src/xsd_to_toml.py --preset fmi2-md --output ./resources/fmi2_md.toml
```

You can also drive it manually by providing `--xsd-root`, `--standard`, `--namespace`, `--name`, and an `--output` path. Headers, dependencies, and forward declarations can be provided via `--headers`, `--dependencies`, and `--forward-declarations` respectively.
