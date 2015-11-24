#include "steppermotor.h"
#include "rotaryencoder.h"
#include "button.h"

#define CCK_LED         13
#define CCK_CLOCKIN     2
#define CCK_ROTEN_A     3
#define CCK_ROTEN_B     4
#define CCK_ROTEN_BTN   6

void stepperInterrupt();

class ChainClock
{
public:
    ChainClock()
        : mRotaryEncoder(CCK_ROTEN_A, CCK_ROTEN_B),
        mButton(CCK_ROTEN_BTN),
        mT0(0),
        mStepCnt(0),
        mIntCnt(0),
        mEncoderValue(0),
        mButtonState(false)
    {
        Serial.begin(115200);
        pinMode(CCK_LED, OUTPUT);
        attachInterrupt(digitalPinToInterrupt(CCK_CLOCKIN), stepperInterrupt, CHANGE);
    }
    void process()
    {
        processStepper();
        processEncoder();
        processButton();
    }
    /*
    ** This ISR hits every 2 seconds, in 100 seconds it needs to make 1 step.
    */
    void stepperInterruptHandler()
    {
        mIntCnt++;
        if (mIntCnt >= 50)
        {
            mStepCnt++;
            mIntCnt = 0;
        }
        led();
    }
protected:
    void processButton()
    {
        bool state = mButton.getButtonState();
        if (state !=  mButtonState)
        {
            mButtonState = state;
            if (state == true)
            {
                Serial.println("Button");
            }
        }
    }

    void processEncoder()
    {
        int encoderValue = mRotaryEncoder.readEncoder();
        if (mEncoderValue != encoderValue)
        {
            mStepCnt -= mEncoderValue - encoderValue;
            mEncoderValue = encoderValue;
        }
    }

    void processStepper()
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
    }
    void led()
    {
        static bool led = true;
        led = !led;
        digitalWrite(CCK_LED, (led ? HIGH : LOW));
    }
    StepperMotor mStepper;
    RotaryEncoder mRotaryEncoder;
    Button mButton;
    long mT0;
    int8_t mStepCnt;
    uint8_t mIntCnt;
    int mEncoderValue;
    bool mButtonState;

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