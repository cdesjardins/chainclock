#ifndef _STEPPER_MOTOR_Hxx
#define _STEPPER_MOTOR_Hxx

class StepperMotor
{
public:
    StepperMotor();
    void stepForward();
    void stepBackward();
protected:
    void stepIt();
    int mStep;
    static int mSteps[];
private:

};

#endif