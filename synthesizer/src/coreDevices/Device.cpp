#include "Device.hpp"

namespace synth {
	
	Device::Device() {
		state = ACTIVE;
	}

	devState_t Device::getState() {
		return state;
	}

	Device::~Device() {
		state = INACTIVE;
	}

}