// MultiStepperDecorateNoLimit.cpp
//
// Copyright (C) 2015 Mike McCauley
// $Id:  $

#include "MultiStepperDecorateNoLimit.h"

MultiStepperDecorateNoLimit::MultiStepperDecorateNoLimit()
    : _num_steppers(0)
{
}

boolean MultiStepperDecorateNoLimit::addStepper(AccelStepperDecorateNoLimit &stepper)
{
    if (_num_steppers >= MULTISTEPPER_MAX_STEPPERS)
	return false; // No room for more
    _steppers_decorate[_num_steppers++] = &stepper;
}



void MultiStepperDecorateNoLimit::moveRelativeDistancesWithPredefinedAccelOrSpeed (double relativeDistance[])
{
    long maxMovingSteps[_num_steppers]; // have not init

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
        maxMovingSteps[i] = _steppers_decorate[i]->dis2Pulses(relativeDistance[i]);
    }

    Serial.println("the steps calculated from distances are:");
    repoertArray(maxMovingSteps);

    moveRelativeStepsWithPredefinedAccelOrSpeed (maxMovingSteps);
    

    // int rangeStatusArr[_num_steppers];
    // getAndReportAllRangeStatus(rangeStatusArr);
}

void MultiStepperDecorateNoLimit::repoertArray(long arr[])
{
	uint8_t i;
	for (i = 0; i < _num_steppers; i++)
	{
		Serial.print(arr[i]); Serial.print(" ");
	}
	Serial.println();
}


void MultiStepperDecorateNoLimit::setConstSpeeds ( double constSpeeds[] )
{
    uint8_t i;
    for ( i = 0; i < _num_steppers; i++ )
    {
        _steppers_decorate[i]->runWithConstSpeed ( constSpeeds[i] );
    }
}


/**
  NOTE: must specify the accel at setup

  Very like the original moveTo, just use predefined accelerate, the cons is that, the steppers stop time will be no relational
  which is acceptable for our usage.
*/
void MultiStepperDecorateNoLimit::moveRelativeStepsWithPredefinedAccelOrSpeed (long relative[])
{

    prepareToGo(); // we call prepareToGo at the very beginning

    uint8_t i;
    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->stepper.move(relative[i]); // New target position (without new speed reset, thus use predefined speed)

    if ( _steppers_decorate[i]->constSpeedMode ) { // set speed when necessary
        _steppers_decorate[i]->stepper.setSpeed ( _steppers_decorate[i]->constSpeed );
    }

    }


    
    runAccelOrSpeedToPosition();

    // int rangeStatusArr[_num_steppers];
    // getAndReportAllRangeStatus(rangeStatusArr);
}



void MultiStepperDecorateNoLimit::prepareToGo()
{
    uint8_t i;

    for (i = 0; i < _num_steppers; i++)
    {
	_steppers_decorate[i]->prepareToGo(); // New target position (without speed reset)
    }
}

// Returns true if any motor is still running to the target position.
boolean MultiStepperDecorateNoLimit::runAccelOrSpeed()
{
    uint8_t i;
    boolean ret = false;
    for (i = 0; i < _num_steppers; i++)
    {
        bool now_stepper_state = _steppers_decorate[i]->run();

        if(now_stepper_state == false){ // either reach the limit or run all required steps, to avoid some steppers run much longer time and let others hot, just stop the stopped ones
            _steppers_decorate[i]->stop();
        }

	   ret = now_stepper_state || ret;
    }
    return ret;
}

// Blocks until all steppers reach their target position and are stopped
void MultiStepperDecorateNoLimit::runAccelOrSpeedToPosition()
{
    while (runAccelOrSpeed ())
	;
}