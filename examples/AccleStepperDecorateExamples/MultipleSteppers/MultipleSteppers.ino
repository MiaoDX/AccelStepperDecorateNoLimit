// MultipleSteppersDecorate.ino
// -*- mode: C++ -*-
// Use MultiStepperDecorate class to manage multiple steppers and make them all move to
// different positions at predefined speed.

#include <AccelStepper.h>
#include <PinsAndConfigurationNoLimit.h>
#include <AccelStepperDecorateNoLimit.h>
#include <MultiStepperDecorateNoLimit.h>


/*
    AccelStepperDecorateNoLimit(char motorName,
                         int dirPin,
                         int stepPin,
                         int enablePin,

                         int subdivision,
                         int reductionRatio,
                         double stepAngle,
                         double maxSpeed,
                         double acceleration,

                         double disPerRound);
*/

AccelStepperDecorateNoLimit stepper1Decorate('Y',
	Y_DIR_PIN,
	Y_STEP_PIN,
	Y_ENABLE_PIN,

	1,
	1,
	1.8,
	600,
    100,

	X_disPerRound
);


AccelStepperDecorateNoLimit stepper2Decorate ('E',
	E_DIR_PIN,
	E_STEP_PIN,
	E_ENABLE_PIN,

	1,
	1,
	1.8,
	600,
    100,

	X_disPerRound
);




// Up to 10 steppers can be handled as a group by MultiStepper
MultiStepperDecorateNoLimit steppersDecorate;


void setup() {
	Serial.begin(9600);

	// Then give them to MultiStepper to manage
	steppersDecorate.addStepper(stepper1Decorate);
	steppersDecorate.addStepper(stepper2Decorate);
}

unsigned long time = 0;
void loop() {

	time = micros ();
    Serial.print ( "Before:" );
    Serial.println ( time );

	// pay attention to the different subdivision of the two steppers, first one with no subdivision, the second one have a subdivision of 32.

	//- Set constSpeed
    double constSpeed = 600.0;
    //stepper1Decorate.runWithConstSpeed ( constSpeed );
    //stepper2Decorate.runWithConstSpeed ( constSpeed );
    double constSpeeds[2] = { constSpeed , constSpeed };
    //steppersDecorate.setConstSpeeds ( constSpeeds );


	//long relative[2] = { -200 * 1 * 40L, -200 * 1 * 40L };
	long relative[2] = { -200 * 1 * 40L, 0 };
	steppersDecorate.moveRelativeStepsWithPredefinedAccelOrSpeed (relative);


	Serial.print ( "After:" );
    Serial.println ( micros () );
    Serial.print ( "Spent:" );
    Serial.println ( micros () - time );
	
	delay(2000);
}