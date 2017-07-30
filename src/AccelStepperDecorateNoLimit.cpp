#include "AccelStepperDecorateNoLimit.h"

AccelStepperDecorateNoLimit::AccelStepperDecorateNoLimit(char motorName,
                                                         int dirPin,
                                                         int stepPin,
                                                         int enablePin,

                                                         int subdivision,
                                                         int reductionRatio,
                                                         double stepAngle,
                                                         double maxSpeed,
                                                         double acceleration,

                                                         double disPerRound)
{
    /*参数赋值*/
    this->motorName = motorName;

    this->enablePin = enablePin;

    this->subdivision = subdivision;
    this->reductionRatio = reductionRatio;

    this->stepAngle = stepAngle;
    this->maxSpeed = maxSpeed * subdivision;
    this->acceleration = acceleration * subdivision;

    this->stepPerRound = 360.0 / this->stepAngle * this->reductionRatio * this->subdivision; //每圈脉冲数
    this->disPerRound = disPerRound;

    this->stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);

    this->setup();

    this->stop();
}

AccelStepperDecorateNoLimit::~AccelStepperDecorateNoLimit()
{
    this->stepper.disableOutputs(); // release all pins
    //delete this->stepper;           // release stepper, HOW TO DO THIS?
}

void AccelStepperDecorateNoLimit::setup()
{

    this->stepper.setPinsInverted(false, false, true); // this is hardcoded, may need some refine.
    this->stepper.setEnablePin(enablePin);

    this->stepper.setMaxSpeed(maxSpeed);
    this->stepper.setAcceleration(acceleration);
}

void AccelStepperDecorateNoLimit::prepareToGo()
{

    // rest current position, to make previous move really stop.
    this->stepper.setCurrentPosition(0);

    this->stepper.enableOutputs();// enable the pins
}

void AccelStepperDecorateNoLimit::runWithConstSpeed ( double constSpeed )
{
    double targetSpeed = constSpeed*this->subdivision;
    if ( this->maxSpeed <  targetSpeed  ) {
        targetSpeed = this->maxSpeed;
        Serial.print ( "Seems that the defined speed is larger than maxSpeed, we reset targetSpeed to :" );
        Serial.println ( targetSpeed );
    }
    
    this->constSpeed = targetSpeed;
    this->stepper.setSpeed ( this->constSpeed );
    this->constSpeedMode = true;
}

long AccelStepperDecorateNoLimit::dis2Pulses(double distance)
{
    return (long)((distance + 0.0) / this->disPerRound * this->stepPerRound); //	脉冲数 = 距离/每圈“距离”*每圈脉冲数
};

bool AccelStepperDecorateNoLimit::run()
{
    if ( this->constSpeedMode ) {
        this->stepper.runSpeedToPosition ();
        return this->stepper.distanceToGo () != 0;
    }

    return this->stepper.run();
}

void AccelStepperDecorateNoLimit::stop()
{
    this->stepper.disableOutputs(); // release all pins
}