#ifndef _STEPPER_MOTOR_Hxx
#define _STEPPER_MOTOR_Hxx

class StepperMotor
{
public:
    StepperMotor();
    void stepForward();
    void stepBackward();
    void setEnabled(bool enable);
    bool getEnabled();

protected:
    void stepIt();
    int mStep;
    static int mSteps[];
    bool mEnabled;
private:

};

#endif