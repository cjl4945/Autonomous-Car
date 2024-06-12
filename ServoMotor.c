#include "msp.h"
#include "TimerA.h"

#define MAX_ANGLE 127

void SERVO_PWM_Init(void)
{
    TIMER_A2_PWM_Init(SystemCoreClock/2000, 0, 1);
}

void SERVO_12OCLOCK(void)
{
    TIMER_A2_PWM_DutyCycle(0.075, 1);
}

void SERVO_3OCLOCK(void)
{
    TIMER_A2_PWM_DutyCycle(0.05, 1);
}

void SERVO_9OCLOCK(void)
{
    TIMER_A2_PWM_DutyCycle(0.1, 1);
}

void SERVO_ANGLE(int angle)
{
    if ((angle >=0) && (angle <= MAX_ANGLE))
    {
        TIMER_A2_PWM_DutyCycle(0.1-((double)angle*(0.05/MAX_ANGLE)), 1);
    }
}
