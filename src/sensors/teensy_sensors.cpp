#include "sensors/teensy_sensors.hpp"

SensorsStatus TeensySensors::get() {
    return {calibrated};
}
void TeensySensors::setCalibrated(bool b) {
    calibrated = b;
}
