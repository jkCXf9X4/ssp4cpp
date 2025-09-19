# Repository Guidelines

## Project Structure & Module Organization
The C++ core lives under `lib/`, split into `common` (shared utilities), `schema` (generated SSP schema types), and `sim` (execution engine). Example apps are in `app/sim`, and reusable resources/SSP archives are stored in `resources/`. Tests live under `tests/` and mirror the library layout (`tests/common`, `tests/sim`, etc.). Vendor code and CMake add-ons reside in `3rdParty/`. Python binding sources are in `lib/python` and depend on generated headers.

## Build, Test, and Development Commands
Use the vcpkg preset when setting up a fresh tree: `cmake --preset=vcpkg`. Incremental work happens via `cmake --build build`. To force a configure, run `cmake -B build -S .`. The main sample executable is `./build/app/sim/sim_app`, which expects SSP archives from `resources/`. Toggle optional components with cache flags such as `cmake -B build -S . -DSSP4CPP_BUILD_TEST=ON -DSSP4CPP_BUILD_PYTHON=ON`.

## Coding Style & Naming Conventions
Match the existing Allman-style braces and 4-space indentation found in `lib/`. Prefer `PascalCase` for types (`Node`, `SystemGraph`) and `snake_case` for functions and variables (`add_child`, `root_path`). Group and alphabetize includes, keeping project headers inside quotes. When touching generated schema files, rerun the XML parser pipeline rather than editing by hand.

## Testing Guidelines
Tests use Catch2 and land in the mirrored folders under `tests/`. Ensure new features ship with focused unit tests and add regression inputs in `resources/` when relevant. After configuring with `SSP4CPP_BUILD_TEST=ON`, build and run the suite via `cmake --build build` followed by `ctest --test-dir build/tests` or directly invoking `./build/tests/test_1`. Prefer descriptive `SECTION` names so failures map cleanly.

## Commit & Pull Request Guidelines
Commit messages in this repository are short and imperative (for example `Prep for applying parameter values`). Keep each commit scoped to one concern and include context in the body when behavior changes. Pull requests should describe motivation, outline testing performed, and link related issues. Attach screenshots or log excerpts when modifying CLI output to simplify review.

## Python & Tooling Notes
Enable `SSP4CPP_BUILD_PYTHON` only when you need the bindings; they reuse the C++ build artifacts. Follow the steps in `readme.md` to create a virtualenv and install `requirements.txt`. Generated bindings land under `build/lib/python`; reinstall with `pip install -e` after rebuilds.
