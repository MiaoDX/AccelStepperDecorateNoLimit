/*
  AccelStepperDecorateNoLimit is a wrapper of `AccelStepper`, the aim is to not change a single line of original lib and just concentrate on what we need.
  Compared with [AccelStepperDecorate](https://github.com/MiaoDX/AccelStepperDecorate) Lib, this do not provide limit function, so lots of variables are not necessary. 

  The functions we need is just:

  dis2steps: change distance to steps, this depends on `disPerRound` which is the movement per round of stepper (can be distance or angel for different purpose)
  run: normal run
  stop: use un-elegant stop, aka just disable all pins instead of run more steps as `AccelStepper` does (stop gently)
*/

#pragma once
#include <AccelStepper.h>

class AccelStepperDecorateNoLimit
{

  public:
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

    ~AccelStepperDecorateNoLimit();

    void setup();
    void prepareToGo(); // we should call prepareToGo at the very beginning, since we rest CurrentPosition by setCurrentPosition(0), this is really an ugly hack, but we have said, we will not pollute the original code of AccelStepper
    void runWithConstSpeed ( double constSpeed );

    long dis2Pulses(double distance);
    bool run();
    void stop();
    

    /*参数定义*/
  public:
    AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, 0, 0);

    char motorName;
    /*pin connection*/

    /*since already have stepper and we won't use this pins anymore, just make them invisable*/
    /*
      int dirPin,              //控制方向管脚
        stepPin,             //输出脉冲管脚
    */
    int enablePin;

    /*configurable parameter*/
    int subdivision = 1,        //细分数
        reductionRatio = 1; //减速比

    bool constSpeedMode = false; // 固定速度
    double constSpeed = 0.0;

    /*static speed parameter*/
    double stepAngle = 1.8, //步距角
        maxSpeed = 300,
        acceleration = 50.0;

    double disPerRound = 0.0; // 电机每圈对应的距离（这个距离可以是直线距离，也可以是角度值！！）

    /*calculate speed parameter*/
    double stepPerRound; //每圈的脉冲数
};
