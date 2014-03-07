#pragma once

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "portaudio.h"
#include "Mixer.hpp"
#include "Module.hpp"
#include "PolyVoice.hpp"
#include "VoiceConfigReader.hpp"
#include "Wavetables.hpp"

namespace chip {
	class AudioProcessor: public AudioEffect {
		public:

			AudioProcessor(int, int, int);

			float * advance(int);

			void cleanup();

			void setVoice(Voice *, int);

			// PortAudio Connection
			int connectToAudioStream();

			int disconnectAudioStream();

			// Activate and release PolyVoices
			void activatePolyVoice(int moduleNum, int note);
			void releasePolyVoice(int moduleNum, int note);

			// PortAudio Callback
			static int paCallback(const void *inputBuffer, void *outputBuffer,
					unsigned long framesPerBuffer,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags, void *userData);

		private:
			PaStream * stream;
			Mixer * masterMixer;
			std::vector<Module*> * audioDeviceList;
	};

}

