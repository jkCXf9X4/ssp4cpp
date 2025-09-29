
import os
import shutil
from pathlib import Path

from fmpy import extract, read_model_description
from fmpy.fmi2 import FMU2Slave

"""
Reference implementation of the Atmos FMU event counter test using FMPy.
"""

REPO_ROOT = Path(os.environ.get("SSP4CPP_PROJECT_ROOT", Path(__file__).resolve().parents[2]))
FMU_PATH = REPO_ROOT / "resources" / "embrace" / "atmos" / "0004_Atmos.fmu"

# Value references taken from resources/embrace/atmos/modelDescription.xml
K_ALT_VR = 352_321_536
K_MACH_VR = 352_321_537
K_DTISA_VR = 16_777_216
K_EVENT_COUNTER_VR = 67_108_867


def run_event_counter_reference() -> None:
    if not FMU_PATH.exists():
        raise FileNotFoundError(f"Expected FMU at {FMU_PATH}")

    unzip_dir = extract(str(FMU_PATH))
    try:
        model_description = read_model_description(str(FMU_PATH))
        co_sim = model_description.coSimulation
        if co_sim is None:
            raise RuntimeError("Atmos FMU does not expose a CoSimulation definition")

        fmu = FMU2Slave(
            guid=model_description.guid,
            unzipDirectory=unzip_dir,
            modelIdentifier=co_sim.modelIdentifier,
            instanceName="atmos-events-reference",
        )

        try:
            fmu.instantiate()
            
            fmu.setupExperiment(startTime=0.0, tolerance=1e-4)
            fmu.enterInitializationMode()
            fmu.setReal([K_DTISA_VR, K_ALT_VR, K_MACH_VR], [0.0, 0.0, 0.0])
            fmu.exitInitializationMode()

            initial_counter = fmu.getReal([K_EVENT_COUNTER_VR])[0]
            print(f"Initial EventCounter: {initial_counter}")

            counter = initial_counter
            alt_der = 10
            mach_der = 1

            step = 0.1

            for step_index in range(1000):
                new_altitude = alt_der * step_index *step
                new_mach = mach_der * step_index *step
                fmu.setReal([K_ALT_VR], [new_altitude])
                fmu.setReal([K_MACH_VR], [new_mach])

                try:
                    fmu.setRealInputDerivatives([K_ALT_VR], [1], [alt_der])
                    fmu.setRealInputDerivatives([K_MACH_VR], [1], [mach_der])
                except Exception as exc:
                    print(f"setRealInputDerivatives not supported: {exc}")

                fmu.doStep(currentCommunicationPoint=step_index * step, communicationStepSize=step)
                counter = fmu.getReal([K_EVENT_COUNTER_VR])[0]
                print(f"EventCounter after step {step_index}: {counter}")

            if counter != initial_counter:
                raise AssertionError("EventCounter did increase during the experiment")
        finally:
            fmu.terminate()
            fmu.freeInstance()
    finally:
        shutil.rmtree(unzip_dir, ignore_errors=True)


if __name__ == "__main__":
    run_event_counter_reference()
