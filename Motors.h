#include "msp.h"
#include "TimerA.h"

#define PWM1_PIN 1
#define PWM2_PIN 2

#define LEFT_FWD_PIN 1
#define LEFT_RWD_PIN 2

#define RIGHT_RWD_PIN 3
#define RIGHT_FWD_PIN 4

void initMotor(void);
void setLeftMotorSpeed(int speed);
void setRightMotorSpeed(int speed);
