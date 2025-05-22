digraph AircraftExtendedSystem {
    // rankdir=LR;
    node [shape=record];

    // d: seconds
    // optional<f>: Hz
    // 

    // ─── Flight-control chain ───────────────────────────────────────────────────
    AirDataSensor     [label="{Air-Data Sensor|d = 0.0|f = 50}"];
    IMU               [label="{Inertia measurement unit|d = 0.0|f = 100}"];
    NavFilter         [label="{Nav Filter|d = 0.005|f = 50}"];
    FCC               [label="{Flight-Control Computer|d = 0.0|f = 60}"];
    FCC_SW1           [label="{FCC_SW1|d = 0.0|f = 30}"];
    FCC_SW2           [label="{FCC_SW2|d = 0.0|f = 15}"];
    FCC_SW3           [label="{FCC_SW3|d = 0.0|f = 60}"];
    FCC_SW4           [label="{FCC_SW4|d = 0.0|f = 30}"];
    ServoActuator     [label="{Servo Actuator|d = 0.005}"];
    ElevatorSurface   [label="{Elevator Surface|d = 0.010}"];

    // ─── Hydraulics ─────────────────────────────────────────────────────────────
    HydraulicPump     [label="{Hydraulic Pump|d = 0.004}"];
    HydraulicManifold [label="{Hydraulic Manifold|d = 0.002}"];

    // ─── Fuel system ───────────────────────────────────────────────────────────
    FuelTankSensor    [label="{Fuel-Tank Sensor|d = 0.0|f = 2}"];
    FuelMgmtComputer  [label="{Fuel-Mgmt Computer|d = 0.005|f = 10}"];
    FuelPump          [label="{Fuel Pump|d = 0.004}"];

    // ─── Engine & FADEC ────────────────────────────────────────────────────────
    EngineFADEC       [label="{Engine FADEC|d = 0.0|f = 100}"];
    EngineCore        [label="{Engine|d = 0.005}"];

    // ─── Recorder ──────────────────────────────────────────────────────────────
    DataRecorder      [label="{Flight-Data Recorder|d = 0.0|f = 1}"];

    // ─── Paths ─────────────────────────────────────────────────────────────────
    // Sensor fusion
    AirDataSensor  -> NavFilter;
    IMU            -> NavFilter;

    // Guidance & control
    NavFilter      -> FCC;
    FCC            -> ServoActuator;
    FCC            -> FCC_SW1;
    FCC_SW1        -> FCC_SW2;
    FCC_SW1        -> FCC_SW3;
    FCC_SW2        -> FCC_SW4;
    FCC_SW3        -> FCC_SW4;
    FCC_SW4        -> FCC;
    ServoActuator  -> ElevatorSurface;

    // Hydraulics power chain
    EngineCore         -> HydraulicPump;          // mechanical drive
    HydraulicPump      -> HydraulicManifold;
    HydraulicManifold  -> ServoActuator;          // pressure feed

    // Fuel chain
    FuelTankSensor     -> FuelMgmtComputer;
    FuelMgmtComputer   -> FuelPump;
    FuelPump           -> EngineCore;             // fuel delivery

    // Engine control loop
    FCC        -> EngineFADEC;                    // throttle demand
    EngineCore -> EngineFADEC;                    // feedback sensing
    EngineFADEC -> EngineCore;                    // fuel/vanes command

    // Monitoring taps
    AirDataSensor    -> DataRecorder;
    FCC              -> DataRecorder;
    ElevatorSurface  -> DataRecorder;
    FuelMgmtComputer -> DataRecorder;
    EngineFADEC      -> DataRecorder;
    EngineCore       -> DataRecorder;
}
