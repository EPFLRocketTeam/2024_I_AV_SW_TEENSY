#ifndef INC_2024_I_AV_TEENSY_TELEMETRY_HPP
#define INC_2024_I_AV_TEENSY_TELEMETRY_HPP

#include "telemetry/telemetry_types.hpp"

struct TelemetryStatus {
	CommandID commandId;
	COMMAND_VALUE commandValue;
};

class TeensyTelemetry {
private:
	CommandID commandId = CMD_NONE;
	COMMAND_VALUE commandValue = 0;

public:
	explicit TeensyTelemetry() {}
    TelemetryStatus get();
    void setCommand(CommandID id, COMMAND_VALUE value);
	void resetCommand();
};

#endif /*INC_2024_I_AV_TEENSY_TELEMETRY_HPP*/