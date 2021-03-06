//Audio Device Class
#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "Device.hpp"
#include "AudioUtils.hpp"

namespace synth {
	// Size of buffer
	static int bufferSize = 64;

	// Sampling rate of the device
	static int sampleRate = 44100;

	class AudioDevice: public virtual Device {
		public:
			AudioDevice();

			// The advance call used to fill a buffer
			virtual sample_t * advance(int) = 0;

			// Perform whatever cleanup is necessary
			virtual void cleanup();

			// Resize the buffer of the audio device
			static void setBufferSize(int);
			// Return the size of the buffer
			static int getBufferSize();

			// Change the sample rate of the audio device
			static void setSampleRate(int);
			// Return the sample rate
			static int getSampleRate();

			virtual ~AudioDevice();
		protected:

			// Set every value in the buffer to 0
			void zeroBuffer();

			// The buffer itself
			sample_t * buffer;

	};
}

