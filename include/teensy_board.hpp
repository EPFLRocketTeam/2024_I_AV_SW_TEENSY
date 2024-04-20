#ifndef INC_2024_I_AV_TEENSY_TEENSY_BOARD_HPP
#define INC_2024_I_AV_TEENSY_TEENSY_BOARD_HPP

#include "config.hpp"
#include "system/system.hpp"
#include "telemetry/teensy_telemetry.hpp"
#include "sensors/teensy_sensors.hpp"

class TeensyBoard {
private:
    SystemClass sys = SystemClass();
    TeensyTelemetry tele = TeensyTelemetry();
    TeensySensors sens = TeensySensors();

    FSMState stateInit();
    FSMState stateCalibration();
    FSMState stateArmed();
    FSMState statePressurize();
    FSMState stateFlightReady();
    FSMState stateIgnite();
    FSMState stateIgnition();
    FSMState stateAscent();
    FSMState stateHovering();
    FSMState stateDescent();
    FSMState stateTouchdown();
    FSMState stateAbort();

    bool armedReady();
    bool pressurizeReady();
    bool flightReadyReady();
    bool igniteReady();
    bool ignitionReady();
    bool ignitionFinishedSuccessfully();

    bool shouldAbort();

public:
    explicit TeensyBoard() {}

    void loopOnce();

    time_millis_t getCurrentTimeMillis();
    void stateUpdate();    
    void acquire();
    void tick();
    void output();
};

#endif /*INC_2024_I_AV_TEENSY_TEENSY_BOARD_HPP*/