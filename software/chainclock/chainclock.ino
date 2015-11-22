#include "steppermotor.h"

class ChainClock
{
public:
    ChainClock()
        : mT0(0)
    {
        Serial.begin(115200);
        pinMode(13, OUTPUT);
    }
    void process()
    {
        long t = millis();
        if ((t - mT0) > 10)
        {
            led();
            mStepper.stepForward();
            mT0 = t;
        }
    }
protected:
    void led()
    {
        static bool led = true;
        led = !led;
        digitalWrite(13, (led ? HIGH : LOW));
        
    }
    StepperMotor mStepper;
    long mT0;
private:
};

ChainClock *g_chainClock;

void setup()
{
    g_chainClock = new ChainClock();
}

void loop()
{
    g_chainClock->process();
}