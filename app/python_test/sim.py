import pyssp4cpp


sim = pyssp4cpp.Simulator("resources/delay_sys.ssp", "resources/config_1.json")
sim.init()
sim.simulate()

