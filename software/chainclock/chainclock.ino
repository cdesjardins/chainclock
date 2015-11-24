#include "steppermotor.h"

#define CCK_LED         13
#define CCK_CLOCKIN     2

void stepperInterrupt();

class ChainClock
{
public:
    ChainClock()
        : mT0(0),
        mStepCnt(0),
        mIntCnt(0)
    {
        Serial.begin(115200);
        pinMode(CCK_LED, OUTPUT);
        attachInterrupt(digitalPinToInterrupt(CCK_CLOCKIN), stepperInterrupt, CHANGE);
    }
    void process()
    {
        long t = millis();
        if ((t - mT0) > 100)
        {
            if (mStepCnt != 0)
            {
                if (mStepper.getEnabled() == false)
                {
                    mStepper.setEnabled(true);
                }
                else
                {
                    processSteps();
                }
            }
            else
            {
                mStepper.setEnabled(false);
            }
            mT0 = t;
        }
    }
    /*
    ** This ISR hits every 2 seconds, in 100 seconds it needs to make 1 step.
    */
    void stepperInterruptHandler()
    {
        mIntCnt++;
        if (mIntCnt >= 50)
        {
            mStepCnt += 1;
            mIntCnt = 0;
        }
        led();
    }
protected:
    void processSteps()
    {
        int stepCnt = 0;
        noInterrupts();
        if (mStepCnt > 0)
        {
            stepCnt = -1;
        }
        else if (mStepCnt < 0)
        {
            stepCnt = 1;
        }
        mStepCnt += stepCnt;
        interrupts();
        if (stepCnt > 0)
        {
            mStepper.stepForward();
        }
        else if (stepCnt < 0)
        {
            mStepper.stepBackward();
        }
        Serial.print(stepCnt, DEC);
        Serial.print(" ");
        Serial.println(mStepCnt, DEC);

    }
    void led()
    {
        static bool led = true;
        led = !led;
        digitalWrite(CCK_LED, (led ? HIGH : LOW));
        
    }
    StepperMotor mStepper;
    long mT0;
    int8_t mStepCnt;
    uint8_t mIntCnt;
private:
};

ChainClock *g_chainClock;

void stepperInterrupt()
{
    g_chainClock->stepperInterruptHandler();
}

void setup()
{
    g_chainClock = new ChainClock();
}

void loop()
{
    g_chainClock->process();
}