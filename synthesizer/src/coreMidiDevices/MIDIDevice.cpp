#include "MIDIDevice.hpp"

chip::MIDIDevice::MIDIDevice() {
	maxNumMIDIDevices = -1;
	MIDIDeviceList = new std::vector<MIDIDevice *>;
	numMIDIDevices = 0;
}

// Forwards all MIDI messages in the stream to all in the MIDIDevice List
void chip::MIDIDevice::affect(MIDIMessage * message) {
	for (int i = 0; i < numMIDIDevices; i++) {
		(*MIDIDeviceList)[i]->affect(message);
	}
}

// Add another MIDIDevice object to be mixed
void chip::MIDIDevice::addMIDIDevice(MIDIDevice* MIDIObject) {
	// Ignore if at maximum value or no maximum
	if (numMIDIDevices < maxNumMIDIDevices || maxNumMIDIDevices == -1) {
		MIDIDeviceList->push_back(MIDIObject);
		numMIDIDevices = MIDIDeviceList->size();
	}
}

// Add a vector of MIDIDevices to be mixed
void chip::MIDIDevice::addMIDIDevices(std::vector<MIDIDevice*> * MIDIObjects) {
	int numToAdd;

	// If no maximum...
	if (maxNumMIDIDevices != -1) {
		// Add all objects
		numToAdd = MIDIObjects->size();
	}
	// ...Or number of devices won't put us at our maximum
	else if ((numMIDIDevices + MIDIObjects->size()) < maxNumMIDIDevices) {
		// Add all objects
		numToAdd = MIDIObjects->size();
	}
	// Else add as many as are available
	else {
		numToAdd = maxNumMIDIDevices - numMIDIDevices;
	}

	MIDIDeviceList->insert(MIDIDeviceList->end(), MIDIObjects->begin(),
			MIDIObjects->begin() + numToAdd);

	numMIDIDevices = MIDIDeviceList->size();
}

// Switch pointer to a new MIDIDeviceList
void chip::MIDIDevice::setMIDIDeviceList(
		std::vector<MIDIDevice*> * MIDIObjects) {

	// Re-reference
	MIDIDeviceList = MIDIObjects;

	// If the new device list has less than the maximum number of devices, or there is no maximum...
	if (MIDIDeviceList->size() < maxNumMIDIDevices || maxNumMIDIDevices == -1) {
		// Then the current number of devices is the size of the new list
		numMIDIDevices = MIDIDeviceList->size();
	} else {
		// Otherwise set to maximum number of devices
		numMIDIDevices = maxNumMIDIDevices;
	}
}

// Remove MIDIDevice objects from the list of the mixer (by object reference)
void chip::MIDIDevice::removeMIDIDevice(MIDIDevice* MIDIObject) {
	for (int i = 0; i < numMIDIDevices; i++) {
		if (MIDIDeviceList->at(i) == MIDIObject) {
			MIDIDeviceList->erase(MIDIDeviceList->begin() + i);
		}
	}
	numMIDIDevices = MIDIDeviceList->size();
}

// Remove IMIDI objects from the list of the mixer (by location)
void chip::MIDIDevice::removeMIDIDevice(int loc) {
	MIDIDeviceList->erase(MIDIDeviceList->begin() + loc);
	numMIDIDevices = MIDIDeviceList->size();
}

// Remove all objects from mixer
void chip::MIDIDevice::removeAllMIDIDevices() {
	while (numMIDIDevices > 0) {
		removeMIDIDevice(0);
	}
}

// Returns the number of objects in this mixer
int chip::MIDIDevice::getNumMIDIDevices() {
	return numMIDIDevices;
}

// Scale a MIDI message to an int
int chip::MIDIDevice::scaleValue(int value, int min, int max) {
	return (value * ((max - min) / 127) + min);
}

// Scale a MIDI message to a float
float chip::MIDIDevice::scaleValue(int value, float min, float max) {
	return (value * ((max - min) / 127) + min);
}

chip::MIDIDevice::~MIDIDevice() {
}
