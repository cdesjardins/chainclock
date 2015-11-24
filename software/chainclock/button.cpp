
#include "button.h"

#define BUTTON_BOUNCE_MASK_ZEROS  0xfff0
#define BUTTON_BOUNCE_MASK_ONES   0xffff

Button::Button(int pin)
    : _buttonState(true),
    _history(0),
    _pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
}

bool Button::getButtonState()
{
    _history = (_history << 1) | digitalRead(_pin) | BUTTON_BOUNCE_MASK_ZEROS;
    if (_history == BUTTON_BOUNCE_MASK_ZEROS)
    {
        _buttonState = false;
    }
    else if (_history == BUTTON_BOUNCE_MASK_ONES)
    {
        _buttonState = true;
    }
    return _buttonState;
}

