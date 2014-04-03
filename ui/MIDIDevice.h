//MIDI Device Class
#ifndef MIDIDEVICE_H
#define MIDIDEVICE_H
#include "Arduino.h"
#include "Device.h"

namespace synth {
	struct MIDIMessage {
			unsigned char statusType;
			unsigned char channel;
			unsigned char data1;
			unsigned char data2;
			int32_t time;
	};

	enum StatusType {
		NOTEOFF = 8,
		NOTEON = 9,
		POLYTOUCH = 10,
		CC = 11,
		PROGRAM = 12,
		MONOTOUCH = 13,
		PITCHBEND = 14,
		SYSTEM = 15
	};

	enum SystemType{
		SYSEX = 0,
		MTC = 1,
		SONGPOSITION = 2,
		SONGSELECT = 3,
		TUNEREQUEST = 6,
		SYSEXEND = 7,
		TIMECLOCK = 8,
		START = 10,
		CONTINUE = 11,
		STOP = 12,
		ACTIVESENSE = 14,
		RESET = 15
	};

	class MIDIDevice: public virtual Device {
		public:
			MIDIDevice();

			// The affect call used to act based on MIDI input
			virtual void affect(MIDIMessage *);

			virtual ~MIDIDevice();
		protected:
			// Scale a MIDI message to an int
			int scaleValue(int value, int min, int max);

			// Scale a MIDI message to a float
			float scaleValue(int value, float min, float max);
	};
}
#endif /*MIDIDevice*/
