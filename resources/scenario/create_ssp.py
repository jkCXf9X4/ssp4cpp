

from pathlib import Path
import OMSimulator as oms



scenario = Path("scenario.fmu").resolve()

ssp_new = Path("scenario.ssp").resolve()

print(f" {scenario=} {ssp_new=}")

oms_inst = oms.OMSimulator()

model = oms.newModel("model")
root = model.addSystem('root', oms.Types.System.WC)
root.addSubModel('scenario', scenario.as_posix())

oms_inst.export("model", ssp_new.as_posix())


## This one removes the string parameter used for changing the scenario
# Need to add this one manually 
ssv = Path("./init_values.ssv")
ssm = Path("./init_values.ssm")
ssp_parameter_set = Path("scenario_parameter.ssp").resolve()

_ = oms_inst.addResources("model", ssv.as_posix())
_ = oms_inst.addResources("model", ssm.as_posix())

oms_inst.referenceResources(
            f"model.root:{ssv.parts[-1]}", ssm.parts[-1]
        )

oms_inst.export("model", ssp_parameter_set.as_posix())
