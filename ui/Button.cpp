#include "Button.h"
namespace ArduinoUI {

	/*
	 * Button wiring:
	 *
	 * Pin     Switch      Ground
	 * o--------o_/ o--------v
	 *
	 */

	Button::Button(int initPin) {
		pin = initPin;
		//Default debounce thresh is 25
		debounceThreshold = 25;
		currentState = 0;
		polledState = 0;
		lastState = 0;
		lastCheckedState = 0;
		debounceCounter = 0;
	}

	void Button::begin() {
		// Sets input mode
		pinMode(pin, INPUT);
		//Gives button a pullup resistor - designed to have the switch connect input pin to ground
		digitalWrite(pin, HIGH);
	}

	int Button::isPressed() {
		// Returns the current state. Note this does nothing without a poll() or pollDebounce() call in the main loop
		return currentState;
	}

	int Button::poll() {
		// Poll without debouncing, just set the state to what the pin is doing
		currentState = (digitalRead(pin) == LOW);
		return currentState;
	}

	int Button::pollDebounce() {
		// Poll the button state
		polledState = (digitalRead(pin) == LOW);
		// If the button is in the same state as the current state, do nothing
		if (polledState != currentState) {
			// Else...

			// Same as last state, checking for continual states
			if (polledState == lastState) {
				// Check if we've had enough continual states
				if (debounceCounter > debounceThreshold) {
					// Set the new state
					currentState = polledState;
					// Reset the debounce counter
					debounceCounter = 0;
				}
				// If we haven't had enough continual states, increment the debounce counter
				else {
					debounceCounter++;
				}
			}
		}
		// Set the next last state as this state, for next polling cycle
		lastState = polledState;
		return currentState;
	}

	int Button::hasChanged() {

		// XOR for a not equal check, represents a change since the last time button was checked
		int notEqual = (currentState ^ lastCheckedState);
		lastCheckedState = currentState;
		return notEqual;
	}

// Set the debounce threshold to a new threshold other than the default 5
	void Button::setDebounceThreshold(int newThreshold) {
		debounceThreshold = newThreshold;
		Serial.println(newThreshold, DEC);
	}

}
