digraph AircraftExtendedSystem {
    // rankdir=LR;
    node [shape=record];

    // d: seconds   ·  optional <f>: Hz
    // ─── Flight-control chain ───────────────────────────────────────────────
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

    // ─── Hydraulics ────────────────────────────────────────────────────────
    HydraulicPump     [label="{Hydraulic Pump|d = 0.004}"];
    HydraulicManifold [label="{Hydraulic Manifold|d = 0.002}"];

    // ─── Fuel system ───────────────────────────────────────────────────────
    FuelTankSensor    [label="{Fuel-Tank Sensor|d = 0.0|f = 2}"];
    FuelMgmtComputer  [label="{Fuel-Mgmt Computer|d = 0.005|f = 10}"];
    FuelPump          [label="{Fuel Pump|d = 0.004}"];

    // ─── Engine & FADEC ────────────────────────────────────────────────────
    EngineFADEC       [label="{Engine FADEC|d = 0.0|f = 100}"];
    EngineCore        [label="{Engine|d = 0.005}"];

    // ─── Recorder ──────────────────────────────────────────────────────────
    DataRecorder      [label="{Flight-Data Recorder|d = 0.0|f = 1}"];

    // ─── Paths (edge delays added) ─────────────────────────────────────────

    // Sensor fusion (AFDX/ARINC-429 data bus ≈ 1–2 ms)
    AirDataSensor  -> NavFilter [label="d = 0.002"];
    IMU            -> NavFilter [label="d = 0.001"];

    // Guidance & control
    NavFilter      -> FCC           [label="d = 0.002"]; // gigabit AFDX frame
    FCC            -> ServoActuator [label="d = 0.004"]; // command bus + drive
    ServoActuator  -> ElevatorSurface  [label="d = 0.0"]; // mech linkage (≪ 1 ms)

    // FCC internal software scheduling (shared RAM / RTOS context switch)
    FCC            -> FCC_SW1  [label="d = 0.0"]; 
    FCC_SW1        -> FCC_SW2  [label="d = 0.0"];
    FCC_SW1        -> FCC_SW3  [label="d = 0.0"];
    FCC_SW2        -> FCC_SW4  [label="d = 0.0"];
    FCC_SW3        -> FCC_SW4  [label="d = 0.0"];
    FCC_SW4        -> FCC  [label="d = 0.0"];

    // Hydraulics power chain (fluid inertia & line length)
    EngineCore        -> HydraulicPump  [label="d = 0.0"];                   // direct shaft (≈ 0)
    HydraulicPump     -> HydraulicManifold [label="d = 0.020"];
    HydraulicManifold -> ServoActuator     [label="d = 0.015"];

    // Fuel chain (fuel-line transit)
    FuelTankSensor    -> FuelMgmtComputer [label="d = 0.005"]; // sensor bus
    FuelMgmtComputer  -> FuelPump         [label="d = 0.002"];
    FuelPump          -> EngineCore       [label="d = 0.100"]; // 5-10m line lag

    // Engine control loop
    FCC         -> EngineFADEC  [label="d = 0.002"]; // throttle command
    EngineCore  -> EngineFADEC  [label="d = 0.0"]; // direct wire
    EngineFADEC -> EngineCore   [label="d = 0.0"]; // direct wire

    // Monitoring taps (shared avionics bus ~1 ms)
    AirDataSensor    -> DataRecorder [label="d = 0.001"];
    FCC              -> DataRecorder [label="d = 0.001"];
    ElevatorSurface  -> DataRecorder [label="d = 0.002"];
    FuelMgmtComputer -> DataRecorder [label="d = 0.002"];
    EngineCore       -> DataRecorder [label="d = 0.001"];
}
