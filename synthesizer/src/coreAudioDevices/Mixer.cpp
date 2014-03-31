#include "Mixer.hpp"
namespace synth {
	Mixer::Mixer(int initBufferSize, int initSampleRate) {
		//constructor
		// Initialize the audio buffers
		temp = (float *) malloc(sizeof(float) * initBufferSize);
		resizeBuffer(initBufferSize);
		changeSampleRate(initSampleRate);
	}

	float * Mixer::advance(int numSamples) {
		if (audioDeviceList->size() == 0) {
			// Zero out the buffer
			zeroBuffer();
		} else {
			// Get the first device's advance buffer and point to it
			buffer = audioDeviceList->front()->advance(numSamples);

			audCallbackIter = audioDeviceList->begin();
			audCallbackIter++;
			// Start at the second item
			//This prevents us from having to iterate through the whole buffer if there's just one item
			while (audCallbackIter != audioDeviceList->end()) {
				//TODO: Restrict maximum number of devices

				// Fill up a temp buffer for one AudioDevice
				temp = (*audCallbackIter)->advance(numSamples);
				// Add each element into the mixdown buffer
				for (int j = 0; j < bufferSize; j++) {
					// Sum each advanced IAudio to the master mixed vector
					buffer[j] += temp[j];
				}
				audCallbackIter++;
			}
		}
		//Pointer to the summed buffer
		return buffer;
	}

	// Sets the maximum number of devices
	void Mixer::setMaxNumAudioDevices(int newMax) {
		// Check if a valid maximum. (-1 indicates no max, 0 indicates no objects)
		if (newMax > -2) {
			maxNumAudioDevices = newMax;
		}

		// If our new maximum is less than our current number of devices, reduce the current device count
		if (maxNumAudioDevices > -1 && numAudioDevices > maxNumAudioDevices) {
			numAudioDevices = maxNumAudioDevices;
		}
	}

	void Mixer::resizeBuffer(int newBufferSize) {
		AudioDevice::resizeBuffer(newBufferSize);
		temp = (float *) realloc(temp, sizeof(float) * newBufferSize);

	}
}
