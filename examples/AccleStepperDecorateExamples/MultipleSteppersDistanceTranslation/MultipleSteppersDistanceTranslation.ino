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

AccelStepperDecorateNoLimit stepper1Decorate ( 'Y',
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


AccelStepperDecorateNoLimit stepper2Decorate ( 'E',
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


void loop() {

	// pay attention to the different subdivision of the two steppers, first one with no subdivision, the second one have a subdivision of 32.

	double relativeDistance[2] = { 2.0*0, -0.2 };
	steppersDecorate.moveRelativeDistancesWithPredefinedAccelOrSpeed (relativeDistance);


	delay(2000); //- running done, first stepper status {rangeStatusArr[0]}, second stepper status {rangeStatusArr[1]}
}