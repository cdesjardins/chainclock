#include "rotaryencoder.h"

RotaryEncoder::RotaryEncoder(int aPin, int bPin)
    : _encoderValue(0),
    _encoderT0(0),
    _aPin(aPin),
    _bPin(bPin)
{
    pinMode(_aPin, INPUT);
    pinMode(_bPin, INPUT);
}
/*
** Return 0 for no rotary encoder movement
** Return 1 for forward movement
** Return -1 for backward movement
*/
int RotaryEncoder::getDirection()
{
    static const int encStates[] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };
    _ab = ((_ab << 2) | ((digitalRead(_aPin) << 1) | digitalRead(_bPin)));
    return (encStates[(_ab & 0x0f)]);
}

int RotaryEncoder::readEncoder()
{
    unsigned long t1;
    int state = getDirection();
    // Only return a knob movement 150ms otherwise the
    // the rotary encoder is way too touchy, and is impossible
    // to accurately control.
    t1 = millis();
    if ((t1 - _encoderT0) > 150)
    {
        if (state != 0)
        {
            _encoderT0 = t1;
            if (state == 1)
            {
                _encoderValue++;
            }
            else
            {
                _encoderValue--;
            }
        }
    }
    return _encoderValue;
}