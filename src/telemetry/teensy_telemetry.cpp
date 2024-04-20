#include "telemetry/teensy_telemetry.hpp"

TelemetryStatus TeensyTelemetry::get() {
	return TelemetryStatus { commandId, commandValue};
}

void TeensyTelemetry::setCommand(CommandID id, COMMAND_VALUE value) {
	commandId = id;
	commandValue = value;

}

void TeensyTelemetry::resetCommand() {
	commandId = CMD_NONE;
	commandValue = 0;
}