#include "arduino.h"
#include "steppermotor.h"

#define CCK_STEPPER_A  11
#define CCK_STEPPER_B  12
#define CCK_STEPPER_C  8
#define CCK_STEPPER_D  9
#define CCK_ENABLE     10

int StepperMotor::mSteps[] = {
    0x0A,
    0x06,
    0x05,
    0x09
};

StepperMotor::StepperMotor()
    : mStep(0)
{
    pinMode(CCK_STEPPER_A, OUTPUT);
    pinMode(CCK_STEPPER_B, OUTPUT);
    pinMode(CCK_STEPPER_C, OUTPUT);
    pinMode(CCK_STEPPER_D, OUTPUT);
    pinMode(CCK_ENABLE, OUTPUT);
    digitalWrite(CCK_ENABLE, HIGH);
}

void StepperMotor::stepForward()
{
    mStep = (mStep + 1) % 4;
    stepIt();
}

void StepperMotor::stepBackward()
{
    mStep = (mStep - 1) % 4;
    stepIt();
}

void StepperMotor::stepIt()
{
    digitalWrite(CCK_STEPPER_A, LOW);
    digitalWrite(CCK_STEPPER_B, LOW);
    digitalWrite(CCK_STEPPER_C, LOW);
    digitalWrite(CCK_STEPPER_D, LOW);
    
    digitalWrite(CCK_STEPPER_A, (mSteps[mStep] & 0x01) ? HIGH : LOW);
    digitalWrite(CCK_STEPPER_B, (mSteps[mStep] & 0x02) ? HIGH : LOW);
    digitalWrite(CCK_STEPPER_C, (mSteps[mStep] & 0x04) ? HIGH : LOW);
    digitalWrite(CCK_STEPPER_D, (mSteps[mStep] & 0x08) ? HIGH : LOW);
}
