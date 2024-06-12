#include "msp.h"
#include "TimerA.h"
#include "Motors.h"

void initMotor(void){
    //Enable Motor 1
    P3->DIR |= BIT6; 
    P3->SEL0 &= ~BIT6;
    P3->SEL1 &= ~BIT6;
    P3->OUT |= BIT6;
    
    //Enable Motor 2
    P3->DIR |= BIT7; 
    P3->SEL0 &= ~BIT7;
    P3->SEL1 &= ~BIT7;
    P3->OUT |= BIT7;
    
    //Generate PWM signals
    TIMER_A0_PWM_Init(SystemCoreClock/10000,0,1);
    TIMER_A0_PWM_Init(SystemCoreClock/10000,0,2);
    TIMER_A0_PWM_Init(SystemCoreClock/10000,0,3);
    TIMER_A0_PWM_Init(SystemCoreClock/10000,0,4);
   
}

void setLeftMotorSpeed(int speed)
{
    if ((speed < 100) && (speed >= 0)) //forward
    {
        TIMER_A0_PWM_DutyCycle(0,PWM2_PIN);
        TIMER_A0_PWM_DutyCycle((double)speed/100,LEFT_FWD_PIN);
    }
    
    if ((speed <= 0) && (speed > -100)) //reverse
    {
        TIMER_A0_PWM_DutyCycle(0,PWM1_PIN);
        TIMER_A0_PWM_DutyCycle((double)(-speed)/100,LEFT_RWD_PIN);
    }
}

void setRightMotorSpeed(int speed)
{
    if ((speed < 100) && (speed >= 0)) //forward
    {
        TIMER_A0_PWM_DutyCycle(0,PWM2_PIN);
        TIMER_A0_PWM_DutyCycle((double)speed/100,RIGHT_FWD_PIN);
    }
    
    if ((speed <= 0) && (speed > -100)) //reverse
    {
        TIMER_A0_PWM_DutyCycle(0,PWM1_PIN);
        TIMER_A0_PWM_DutyCycle((double)(-speed)/100,RIGHT_RWD_PIN);
    }
}
