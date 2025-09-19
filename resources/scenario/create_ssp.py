

from pathlib import Path
import OMSimulator as oms



scenario = Path("scenario.fmu").resolve()

ssp_new = Path("scenario.ssp").resolve()

print(f" {scenario=} {ssp_new=}")

model = oms.newModel("model")
root = model.addSystem('root', oms.Types.System.WC)
root.addSubModel('scenario', scenario.as_posix())

oms.OMSimulator().export("model", ssp_new.as_posix())