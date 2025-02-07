#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "Uart.h"

void myDelay(int del);
    
int TIMER_A0_PWM_Init(uint16_t period, double percentDutyCycle, uint16_t pin);
void TIMER_A0_PWM_DutyCycle(double percentDutyCycle, uint16_t pin);

int TIMER_A2_PWM_Init(uint16_t period, double percentDutyCycle, uint16_t pin);
void TIMER_A2_PWM_DutyCycle(double percentDutyCycle, uint16_t pin);
