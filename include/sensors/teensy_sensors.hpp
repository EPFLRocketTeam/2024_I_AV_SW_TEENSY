#ifndef INC_2024_I_AV_TEENSY_TEENSY_SENSORS_HPP
#define INC_2024_I_AV_TEENSY_TEENSY_SENSORS_HPP

struct SensorsStatus {
    bool calibrated;
};

class TeensySensors {
public:
    explicit TeensySensors() {}

    SensorsStatus get();
    void setCalibrated(bool b);

private:
    bool calibrated = false;
};

#endif /* INC_2024_I_AV_TEENSY_TEENSY_SENSORS_HPP */