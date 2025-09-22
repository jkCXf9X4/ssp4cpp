# Repository Guidelines

## Project Structure & Module Organization
The C++ core lives under `lib/`, with `lib/common` for shared utilities, `lib/schema` for generated SSP model types (do not edit manually; rerun the XML parser), and `lib/sim` for runtime logic. Example apps live in `app/sim`; reusable SSP archives and fixtures are in `resources/`. Tests mirror the layout inside `tests/`. Third-party CMake modules and vendored sources are in `3rdParty/`. Generated Python bindings appear in `build/lib/python` after a binding build.

## Build, Test, and Development Commands
Run `cmake --preset=vcpkg` before first compilation to pull toolchains and configure the build. Use `cmake --build build` for incremental C++ builds; append `--target sim_app` to focus on the sample executable. Reconfigure options with `cmake -B build -S . -DSSP4CPP_BUILD_TEST=ON -DSSP4CPP_BUILD_PYTHON=ON`. Launch the sample via `./build/app/sim/sim_app resources/demo.ssp`. Activate the Python bindings only when needed: `pip install -e build/lib/python`.

## Coding Style & Naming Conventions
Follow Allman braces and 4-space indentation seen in `lib/`. Use `PascalCase` for types (`Node`, `SystemGraph`) and `snake_case` for functions, variables, and filenames. Place standard headers first, then project headers grouped and alphabetized. Prefer `spdlog` helpers from `lib/common` for logging; avoid raw `std::cout`. Regenerate schema code instead of hand-editing files under `lib/schema`.

## Testing Guidelines
Enable tests with `cmake -B build -S . -DSSP4CPP_BUILD_TEST=ON`, then build via `cmake --build build --target test_1`. Run suites directly (`./build/tests/test_1`). Create new Catch2 cases in mirrored directories (`tests/sim/...`). Use descriptive `TEST_CASE` and `SECTION` names, and add regression archives to `resources/` when a bug fix needs coverage.

## Commit & Pull Request Guidelines
Write short, imperative commit subjects (e.g., `Guard against empty signals`). Scope each commit to one concern and document behavior or migration notes in the body. PR descriptions should outline motivation, summarize functional changes, list verification steps (commands or logs), and link issues. Include screenshots or sample output when altering CLI text so reviewers can compare results.

## Python & Tooling Notes
Enable `SSP4CPP_BUILD_PYTHON` only when you need the bindings; they reuse the C++ build artifacts.
`cmake -B build -S . -DSSP4CPP_BUILD_PYTHON=ON`
 Follow the steps in `readme.md` to create a virtualenv and install `requirements.txt`. Generated bindings land under `build/lib/python`; reinstall with `pip install -e` after rebuilds.
