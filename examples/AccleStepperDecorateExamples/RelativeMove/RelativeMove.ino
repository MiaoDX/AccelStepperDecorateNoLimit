// MultipleSteppersDecorateNoLimit.ino
// -*- mode: C++ -*-
// Make a single stepper some relative steps from one limit to another
// 
// This is just a minimum stepper to show how the AccelStepperDecorate Library work.

#include <AccelStepper.h>
#include <PinsAndConfigurationNoLimit.h>
#include <AccelStepperDecorateNoLimit.h>


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

/*
* Note that this stepper is hard coded enable pin as reversed
* so if your shield or board connection won't run at all, just check this
*
* The Limit pins (MIN_PIN and MAX_PIN) are set to be unset (outRangeSwitch == false), so don't have to do extra wire connection.
* and thus the maxMovingDistance is also useless.
*
* The subdivision is set to 1 (no subdivision)
*/
AccelStepperDecorateNoLimit stepper1Decorate('X',
	E_DIR_PIN,
	E_STEP_PIN,
	E_ENABLE_PIN,

	1,
	1,
	1.8,
	1000,
    100,

	X_disPerRound
);


void setup() {
	Serial.begin(9600);
}


unsigned long time = 0;
void loop() {

    time = micros ();
    Serial.print ( "Before:" );
    Serial.println ( time );
	long relative = -200 * 1 * 20L;

	stepper1Decorate.prepareToGo();

	stepper1Decorate.stepper.move(relative); // this is really ugly.
                                             
    /* We must set the speed after the move, which is not so ideal, but we have no choice since we CAN not change the original code */
    /* So we should take care in the multiSteppers */
    double constSpeed = 600.0;
    //stepper1Decorate.runWithConstSpeed ( constSpeed );
    Serial.println ( stepper1Decorate.stepper.speed () );

    

	// wait to finish the run
    while ( stepper1Decorate.run () ) {
        ; // idle wait
        if ( stepper1Decorate.stepper.distanceToGo () % 1000 == 0 ) {
            //Serial.println ( stepper1Decorate.stepper.speed () );
        }
    }
		

	stepper1Decorate.stop();

    Serial.print ( "After:" );
    Serial.println ( micros () );
    Serial.print ( "Spent:" );
    Serial.println ( micros () - time );

	delay(2000);
}