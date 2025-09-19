

from pathlib import Path
from OMSimulator import OMSimulator


ssp = Path("embrace.ssp").resolve()
scenario = Path("./../scenario/scenario.fmu").resolve()
ssp_new = Path("embrace_scen.ssp").resolve()

print(f"{ssp=}, {scenario=} {ssp_new=}")

oms = OMSimulator()
ref, _ = oms.importFile(ssp.as_posix())

print(ref)

oms.addSubModel('model.root.Scenario', scenario.as_posix())

#   <ssd:Connection startElement="bc" startConnector="Alt"              endElement="Consumer"     endConnector="Alt" />
#   <ssd:Connection startElement="bc" startConnector="Mach"             endElement="Consumer"     endConnector="Mach" />
#   <ssd:Connection startElement="bc" startConnector="heat_load"        endElement="Consumer"     endConnector="heatLoad" />
#   <ssd:Connection startElement="bc" startConnector="Alt"              endElement="ECS_HW"       endConnector="Alt" />
#   <ssd:Connection startElement="bc" startConnector="Mach"             endElement="ECS_HW"       endConnector="Mach" />
#   <ssd:Connection startElement="bc" startConnector="Aircraft_state"   endElement="AdaptionUnit" endConnector="Aircraft_State" />
#   <ssd:Connection startElement="bc" startConnector="Alt"              endElement="Atmos"        endConnector="Alt" />
#   <ssd:Connection startElement="bc" startConnector="Mach"             endElement="Atmos"        endConnector="Ma" />

oms.addConnection("model.root.Scenario.Alt", "model.root.Consumer.Alt")
oms.addConnection("model.root.Scenario.Mach", "model.root.Consumer.Mach")
oms.addConnection("model.root.Scenario.heat_load", "model.root.Consumer.heatLoad")
oms.addConnection("model.root.Scenario.Alt", "model.root.ECS_HW.Alt")
oms.addConnection("model.root.Scenario.Mach", "model.root.ECS_HW.Mach")
oms.addConnection("model.root.Scenario.Aircraft_state", "model.root.AdaptionUnit.Aircraft_State")
oms.addConnection("model.root.Scenario.Alt", "model.root.Atmos.Alt")
oms.addConnection("model.root.Scenario.Mach", "model.root.Atmos.Ma")

oms.export("model", ssp_new.as_posix())


# oms.setResultFile("model", "results.csv")
# oms.setStopTime("model", 0.1)
# oms.setFixedStepSize("model.root", 1e-4)

# oms.instantiate("model")

# oms.initialize("model")
# oms.simulate("model")
# oms.terminate("model")
# oms.delete("model")
