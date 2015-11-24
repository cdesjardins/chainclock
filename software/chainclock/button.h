#ifndef _BUTTON_Hxx
#define _BUTTON_Hxx
#include <Arduino.h>

class Button
{
public:
    Button(int pin);
    // returns TRUE if button pin is 1
    // false otherwise
    bool getButtonState();
private:
    bool _buttonState;
    int16_t _history;
    int _pin;
};

#endif