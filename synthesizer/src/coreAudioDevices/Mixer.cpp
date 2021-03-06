#include "Mixer.hpp"
namespace synth {
	Mixer::Mixer() {
	}

	sample_t * Mixer::advance(int numSamples) {
		if (!isEmpty()) {
			// Grab the first item in the list and copy its buffer over first
			memcpy(buffer, front()->advance(numSamples),
					sizeof(sample_t) * numSamples);

			deviceIter = begin();
			deviceIter++;
			// Start at the second item
			while (deviceIter != end()) {
				// Add each element into the mixdown buffer
				for (int j = 0; j < numSamples; j++) {
					// Sum each advanced AudioDevice to the master mixed vector
					buffer[j] += *((*deviceIter)->advance(1));
				}
				deviceIter++;
			}
		}
		else{
			// Zero out the buffer
			zeroBuffer();
		}
		//Pointer to the summed buffer
		return buffer;
	}

}
