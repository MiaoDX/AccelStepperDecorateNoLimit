// MultiStepperDecorateNoLimit.h

#ifndef MultiStepperDecorateNoLimit_h
#define MultiStepperDecorateNoLimit_h

#include <stdlib.h>
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <wiring.h>
#endif

#define MULTISTEPPER_MAX_STEPPERS 10

#include "AccelStepperDecorateNoLimit.h"

//class AccelStepperDecorateNoLimit;

/*
  MultiStepperDecorateNoLimit, change from `MultiStepper`, to support StepperDecorate and make things easier to NOT
  make a liner run, just a predefined maxspeed and accelerate
*/

class MultiStepperDecorateNoLimit
{
  public:
    /// Constructor
    MultiStepperDecorateNoLimit();

    /// Add a stepper to the set of managed steppers
    /// There is an upper limit of MULTISTEPPER_MAX_STEPPERS = 10 to the number of steppers that can be managed
    /// \param[in] stepper Reference to a stepper to add to the managed list
    /// \return true if successful. false if the number of managed steppers would exceed MULTISTEPPER_MAX_STEPPERS
    boolean addStepper( AccelStepperDecorateNoLimit &stepperDecorate);

    void moveRelativeDistancesWithPredefinedAccelOrSpeed(double relativeDistance[]);
    void moveRelativeStepsWithPredefinedAccelOrSpeed(long relative[]);

    void setConstSpeeds ( double constSpeeds[] );

    void prepareToGo();

    boolean runAccelOrSpeed ();

    void runAccelOrSpeedToPosition();

	void repoertArray(long arr[]);
  private:
    /// Array of pointers to the steppers we are controlling.
    /// Fills from 0 onwards
      AccelStepperDecorateNoLimit *_steppers_decorate[MULTISTEPPER_MAX_STEPPERS];

    /// Number of steppers we are controlling and the number
    /// of steppers in _steppers[]
    uint8_t _num_steppers;
};

/// @example MultiStepper.pde
/// Use MultiStepper class to manage multiple steppers and make them all move to
/// the same position at the same time for linear 2d (or 3d) motion.

#endif
