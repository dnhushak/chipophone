#include "MIDIDevice.h"
#include <stdio.h>
#include <unistd.h>
#include "Arduino.h"
#include <HardwareSerial.h>

namespace synth {

	class ArduinoMIDIHandler: public MIDIDevice {
		public:
			ArduinoMIDIHandler(HardwareSerial * port);

			void begin();

			// Read from the FIFO serial stream
			void readMIDI();

			// Write to the output stream
			void writeMIDI(MIDIMessage* message);

			virtual ~ArduinoMIDIHandler();

		private:
			HardwareSerial * MIDIport;
	};

}