#include "teensy_board.hpp"

void TeensyBoard::stateUpdate() {
	FSMState current = sys.get().state;
	FSMState next = ABORT_STATE;

    switch (current) {
        case INIT_STATE:
			next = stateInit();
		case CALIBRATION_STATE:
			next = stateCalibration();
		case ARMED_STATE:
			next = stateArmed();
		case PRESSURIZE_STATE:
			next = statePressurize();
		case FLIGHTREADY_STATE:
			next = stateFlightReady();
		case IGNITE_STATE:
			next = stateIgnite();
		case IGNITION_STATE:
			next = stateIgnition();
		case ASCENT_STATE:
			next = stateAscent();
		case HOVERING_STATE:
			next = stateHovering();
		case DESCENT_STATE:
			next = stateDescent();
		case TOUCHDOWN_STATE:
			next = stateTouchdown();
		case ABORT_STATE:
			next = stateAbort();
	}

	sys.setState(next);

    if (current != next) {
		sys.setLastFsmTransition(sys.get().time);
	}

    // TODO DMA to rpi
}

void TeensyBoard::acquire() {

}

void TeensyBoard::tick() {

}

void TeensyBoard::output() {
    
}

FSMState TeensyBoard::stateInit() {
    TelemetryStatus teleStatus = tele.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case CALIBRATION_STATE:
                sens.setCalibrated(false);
                return CALIBRATION_STATE;

            case ARMED_STATE:
                if(!armedReady()) break;
                return ARMED_STATE;
            default:
                break;
        }
    }

    return INIT_STATE;
}

FSMState TeensyBoard::stateCalibration() {
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    time_millis_t calibratingSince = sysStatus.time - sysStatus.lastFSMTransition;

    // If calibration is finished, return to INIT
    if(calibratingSince >= CALIBRATION_DURATION_MS) {
        sens.setCalibrated(true);
        return INIT_STATE;
    }
    
    return CALIBRATION_STATE;
}

FSMState TeensyBoard::stateArmed() {
    if(shouldAbort())
        return ABORT_STATE;
           
    TelemetryStatus teleStatus = tele.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case INIT_STATE:
                return INIT_STATE;
            case ABORT_STATE:
                return ABORT_STATE;
            case PRESSURIZE_STATE:
                if(!pressurizeReady()) break;
                return PRESSURIZE_STATE;
            default:
                break;
        }
    }

    return ARMED_STATE;

}

FSMState TeensyBoard::statePressurize() {
    if(shouldAbort())
        return ABORT_STATE;
        
    TelemetryStatus teleStatus = tele.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            case FLIGHTREADY_STATE:
                flightReadyReady();
                return FLIGHTREADY_STATE;
            default:
                break;
        }
    }

    return PRESSURIZE_STATE;
}

FSMState TeensyBoard::stateFlightReady() {
    if(shouldAbort())
        return ABORT_STATE;

    TelemetryStatus teleStatus = tele.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            case IGNITE_STATE:
                if(!igniteReady()) break;
                return IGNITE_STATE;
            default:
                break;
        }
    }

    return FLIGHTREADY_STATE;
}


FSMState TeensyBoard::stateIgnite() {
    if(shouldAbort())
        return ABORT_STATE;
           
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            default:
                break;
        }
    }

    if(ignitionReady())
        return IGNITION_STATE;

    return IGNITE_STATE;
}

FSMState TeensyBoard::stateIgnition() {
    if(shouldAbort())
        return ABORT_STATE;
           
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            default:
                break;
        }
    }

    if(ignitionFinishedSuccessfully())
        return ASCENT_STATE;

    return IGNITION_STATE;
}

// TODO stateIgnition

FSMState TeensyBoard::stateAscent() {
    if(shouldAbort())
        return ABORT_STATE;
           
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            default:
                break;
        }
    }

    if(sysStatus.time - sysStatus.lastFSMTransition >= ASCENT_DURATION_MS)
        return HOVERING_STATE;

    return ASCENT_STATE;
}

FSMState TeensyBoard::stateHovering() {
    if(shouldAbort())
        return ABORT_STATE;
    
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            default:
                break;
        }
    }

    if(sysStatus.time - sysStatus.lastFSMTransition >= HOVERING_DURATION_MS)
        return DESCENT_STATE;

    return HOVERING_STATE;
}

FSMState TeensyBoard::stateDescent() {
    if(shouldAbort())
        return ABORT_STATE;
    
    TelemetryStatus teleStatus = tele.get();
    SystemStatus sysStatus = sys.get();

    if(teleStatus.commandId == CMD_AV_STATE) {
        FSMState nextState = (FSMState) teleStatus.commandValue;
        tele.resetCommand();

        switch(nextState) {
            case ABORT_STATE:
                return ABORT_STATE;
            default:
                break;
        }
    }

    if(sysStatus.time - sysStatus.lastFSMTransition >= DESCENT_DURATION_MS)
        return TOUCHDOWN_STATE;

    return DESCENT_STATE;
}

FSMState TeensyBoard::stateTouchdown() {
    if(shouldAbort())
        return ABORT_STATE;
    
    SystemStatus sysStatus = sys.get();

    return TOUCHDOWN_STATE;
}