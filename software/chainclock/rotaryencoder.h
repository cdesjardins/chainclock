#ifndef _ROTARY_ENCODER_Hxx
#define _ROTARY_ENCODER_Hxx

#include <Arduino.h>

class RotaryEncoder
{
public:
    RotaryEncoder(int aPin, int bPin);
    int readEncoder();

private:
    int getDirection();

    int _encoderValue;
    unsigned long _encoderT0;
    uint8_t _ab;
    int _aPin;
    int _bPin;
};
#endif