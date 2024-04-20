#include "system/system.hpp"

SystemStatus SystemClass::get() {
	return SystemStatus {time, lastFSMTransition, state};
}

void SystemClass::setTime(time_millis_t timeIn) {
	time = timeIn;
}

void SystemClass::setLastFsmTransition(time_millis_t lastFsmTransitionIn) {
	lastFSMTransition = lastFsmTransitionIn;
}

void SystemClass::setState(FSMState stateIn) {
	state = stateIn;
}