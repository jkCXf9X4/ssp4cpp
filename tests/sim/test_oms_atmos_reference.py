"""Reference script demonstrating the Atmos FMU event counter flow with OMSimulator.

This mirrors the Catch2 test "Atmos FMU reports solver events via EventCounter"
and the FMPy reference script. It assumes OMSimulator's Python bindings are
installed and available as `OMSimulator`.
"""

from __future__ import annotations

import math
import os
import shutil
import tempfile
from pathlib import Path

from OMSimulator import OMSimulator

REPO_ROOT = Path(
    os.environ.get("SSP4CPP_PROJECT_ROOT", Path(__file__).resolve().parents[2])
)
FMU_PATH = REPO_ROOT / "resources" / "embrace" / "atmos" / "0004_Atmos.fmu"

MODEL_NAME = "model"
SYSTEM_PATH = f"{MODEL_NAME}.root"
SUBMODEL_PATH = f"{SYSTEM_PATH}.atmos"

ALT_PATH = f"{SUBMODEL_PATH}.Alt"
MACH_PATH = f"{SUBMODEL_PATH}.Ma"
DTISA_PATH = f"{SUBMODEL_PATH}.DTisa"
EVENT_COUNTER_PATH = f"{SUBMODEL_PATH}.EventCounter"

step = 1e-3
tolerance: float = 1e-4
stop_time = 10
alt_der = 10
mach_der = 1


def run_oms_reference() -> None:
    print("\n\n-------------\nrun_oms_reference")

    if not FMU_PATH.exists():
        raise FileNotFoundError(f"Expected FMU at {FMU_PATH}")

    tmp_dir = tempfile.mkdtemp(prefix="oms_atmos_")
    try:
        oms = OMSimulator()

        oms.setTempDirectory(tmp_dir + os.sep)
        oms.setCommandLineOption("--suppressPath=true")
        oms.setCommandLineOption("--ignoreInitialUnknowns=true")
        oms.setCommandLineOption("--suppressPath=true")
        oms.setCommandLineOption("--wallTime=true")
        oms.setCommandLineOption("--emitEvents=false")

        oms.setCommandLineOption("--inputExtrapolation=true")

        oms.newModel(MODEL_NAME)
        oms.addSystem(SYSTEM_PATH, oms.system_wc)
        oms.addSubModel(SUBMODEL_PATH, str(FMU_PATH))

        oms.setStartTime(MODEL_NAME, float(0.0))
        oms.setStopTime(MODEL_NAME, stop_time)
        oms.setTolerance(SYSTEM_PATH, tolerance, tolerance)
        oms.setResultFile(MODEL_NAME, "")  # disable result file generation
        oms.setFixedStepSize(SYSTEM_PATH, step)

        oms.instantiate(MODEL_NAME)

        oms.setReal(DTISA_PATH, 0.0)
        oms.setReal(ALT_PATH, 0.0)
        oms.setReal(MACH_PATH, 0.0)

        oms.initialize(MODEL_NAME)

        initial_counter = oms.getReal(EVENT_COUNTER_PATH)
        print(f"Initial EventCounter: {initial_counter}")

        counter = initial_counter

        for step_index in range(int(stop_time / step)):
            time = step_index * step

            new_altitude = alt_der * time
            new_mach = mach_der * time

            oms.setReal(ALT_PATH, new_altitude)
            oms.setReal(MACH_PATH, new_mach)

            try:
                oms.setRealInputDerivative(ALT_PATH, alt_der)
                oms.setRealInputDerivative(MACH_PATH, mach_der)
            except Exception as exc:
                print(f"setRealInputDerivative not supported: {exc}")

            status = oms.doStep(MODEL_NAME)


        counter = oms.getReal(EVENT_COUNTER_PATH)
        if counter > initial_counter:
            print(f"EventCounter ({counter[0]}) did increase during the experiment")

    finally:
        try:
            oms.terminate(MODEL_NAME)
        except Exception:
            pass
        oms.delete(MODEL_NAME)
        shutil.rmtree(tmp_dir, ignore_errors=True)


def run_oms_reference2() -> None:
    print("\n\n-------------\nrun_oms_reference2")
    if not FMU_PATH.exists():
        raise FileNotFoundError(f"Expected FMU at {FMU_PATH}")

    tmp_dir = tempfile.mkdtemp(prefix="oms_atmos_")
    tmp_dir = Path(tmp_dir)
    try:
        oms = OMSimulator()

        oms.setTempDirectory(tmp_dir.as_posix())
        oms.setCommandLineOption("--suppressPath=true")
        oms.setCommandLineOption("--ignoreInitialUnknowns=true")
        oms.setCommandLineOption("--suppressPath=true")
        oms.setCommandLineOption("--wallTime=true")
        oms.setCommandLineOption("--emitEvents=false")

        oms.setCommandLineOption("--inputExtrapolation=true")

        oms.newModel(MODEL_NAME)
        oms.addSystem(SYSTEM_PATH, oms.system_wc)
        oms.addSubModel(SUBMODEL_PATH, str(FMU_PATH))

        res_file = tmp_dir / "res.csv"
        oms.setStartTime(MODEL_NAME, float(0.0))
        oms.setStopTime(MODEL_NAME, stop_time)
        oms.setTolerance(SYSTEM_PATH, tolerance, tolerance)
        oms.setResultFile(MODEL_NAME, res_file.as_posix())
        oms.setFixedStepSize(SYSTEM_PATH, step)

        oms.instantiate(MODEL_NAME)

        oms.initialize(MODEL_NAME)

        initial_counter = oms.getReal(EVENT_COUNTER_PATH)
        print(f"Initial EventCounter: {initial_counter}")

        bc_file = tmp_dir / "bc.csv"

        with open(bc_file, "w") as f:
            f.write("time,alt,ma\n")
            for i in range(int(stop_time)):
                f.write(f"{i}, {alt_der * i}, {mach_der * i}\n")

        with open(bc_file, "r") as f:
            print(f.readlines())

        oms.addSubModel("model.root.bc", bc_file.as_posix())

        oms.addConnection("model.root.bc.alt", ALT_PATH)
        oms.addConnection("model.root.bc.ma", MACH_PATH)

        oms.simulate(MODEL_NAME)

        counter = oms.getReal(EVENT_COUNTER_PATH)
        print(f"EventCounter after sim: {counter}")

        with open(tmp_dir / "res.csv", "r") as f:
            pass
            # print(f.readlines()[0:4])

        if counter == initial_counter:
            print(f"EventCounter ({counter[0]}) did not increase during the experiment")

    finally:
        try:
            oms.terminate(MODEL_NAME)
        except Exception:
            pass
        oms.delete(MODEL_NAME)
        shutil.rmtree(tmp_dir, ignore_errors=True)


if __name__ == "__main__":
    run_oms_reference()
    run_oms_reference2()
