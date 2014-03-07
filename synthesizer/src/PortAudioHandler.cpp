#include "PortAudioHandler.hpp"

namespace chip {

	// Setup and start a PortAudio Stream
	PaError PortAudioHandler::ConnectAudioStream(int bufferSize, int sampleRate,
			PaDeviceIndex devID, int numChannels, void *userData) {

		// Declare output parameters
		PaStreamParameters outputParameters;

		// Initialize PA
		err = Pa_Initialize();
		if (err != paNoError)
			return errorPortAudio(err);

		// Set output Parameters
		outputParameters.device = devID;
		if (outputParameters.device == paNoDevice)
			return errorPortAudio(err);
		outputParameters.channelCount = numChannels;
		outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
		outputParameters.suggestedLatency = Pa_GetDeviceInfo(
				outputParameters.device)->defaultLowOutputLatency;
		outputParameters.hostApiSpecificStreamInfo = NULL;

		// Open the stream
		err = Pa_OpenStream(&stream, NULL, &outputParameters, sampleRate,
				bufferSize, paNoFlag, /* we won't output out of range samples so don't bother clipping them */
				PortAudioHandler::paCallback, userData); // We want to pass a pointer to the AudioProcessor
		if (err != paNoError)
			return errorPortAudio(err);

		// Start the stream
		err = Pa_StartStream(stream);
		if (err != paNoError)
			return errorPortAudio(err);

		return err;
	}

	// Stop a PortAudio stream
	PaError PortAudioHandler::DisconnectAudioStream() {
		PaError err;
		err = Pa_StopStream(stream);
		if (err != paNoError)
			errorPortAudio(err);

		err = Pa_CloseStream(stream);
		if (err != paNoError)
			errorPortAudio(err);

		return err;
		Pa_Terminate();

	}

	// PortAudio Error Check
	PaError PortAudioHandler::errorPortAudio(PaError err) {
		Pa_Terminate();
		fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error number: %d\n", err);
		fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
		printAudioDevices();
		return err;
	}

	// Print a list of valid devices
	void static PortAudioHandler::printAudioDevices() {
		printf("***Valid Audio Devices: ***");
		Pa_Initialize();
		int ndev;
		ndev = Pa_GetDeviceCount();
		for (int i = 0; i < ndev; i++) {
			const PaDeviceInfo * info = Pa_GetDeviceInfo((PaDeviceIndex) i);
			if (info->maxOutputChannels > 0) {

				if (info->maxInputChannels > 0) {
					printf("Input/Output Device:    ");
				} else {
					printf("Output Device:          ");
				}
			} else {
				if (info->maxInputChannels > 0) {
					printf("Input Device:           ");
				} else {
					printf("Device:                 ");
				}

			}
			printf("%d: %s\n", i, info->name);
		}

		PaDeviceIndex defaultin = Pa_GetDefaultInputDevice();
		PaDeviceIndex defaultout = Pa_GetDefaultOutputDevice();
		const PaDeviceInfo * inputinfo = Pa_GetDeviceInfo(
				(PaDeviceIndex) defaultin);
		const PaDeviceInfo * outputinfo = Pa_GetDeviceInfo(
				(PaDeviceIndex) defaultout);
		printf("Default Input Device:   %d: %s\n", defaultin, inputinfo->name);
		printf("Default Output Device:  %d: %s\n", defaultout,
				outputinfo->name);

	}

	// PortAudio Callback
	int PortAudioHandler::paCallback(const void *inputBuffer,
			void *outputBuffer, unsigned long framesPerBuffer,
			const PaStreamCallbackTimeInfo* timeInfo,
			PaStreamCallbackFlags statusFlags, void *userData) {

		// Cast void type outbut buffer to float
		float *out = (float*) outputBuffer;

		// Grab the supplied user data
		chip::AudioProcessor * audio = (chip::AudioProcessor*) userData;

		// Fill the output buffer
		out = audio->advance(framesPerBuffer);

		// Continue
		return paContinue;
	}

}
