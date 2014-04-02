#ifndef BUTTON_H_
#define BUTTON_H_

#include "Arduino.h"
namespace UI {
class Button {
  public:
    Button(int initPin);
    int isPressed();
    int pollDebounce();
    void begin();
    int poll();
    void setDebounceThreshold(int newThreshold);

  private:
    int pin;
    // True represents pressed
    int currentState;

    // Last state is the last polled state (for debouncing)
    int lastState;
    // Polled state is the state on this current poll loop;
    int polledState;
    // A counter to count cycles for debouncing
    short debounceCounter;

    // The threshold of clock cycles to count for an actual press
    short debounceThreshold;
};

}
#endif //BUTTON_H_
