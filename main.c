/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* LJBeato
* 1/14/2021
*
* Filename: main_timer_template.c
*/
#include <stdio.h>
#include <stdlib.h>

#include "msp.h"
#include "uart.h"
#include "led.h"
#include "switches.h"
#include "Timer32.h"
#include "CortexM.h"
#include "Common.h"
#include "ADC14.h"
#include "ControlPins.h"
#include "ServoMotor.h"
#include "Motors.h"

#define SLOW_SPEED 30
#define FAST_SPEED 33

#define SLOW_TURN_SPEED 27
#define FAST_TURN_SPEED 30



///////////////////////////////////////////////////////
//
// NOTE: For the camera, you may want to change the default
//       clock to 48MHz
//
// To do that: Edit system_msp432p401r.c
//             Change:   #define  __SYSTEM_CLOCK    3000000
//             To:       #define  __SYSTEM_CLOCK    48000000 
// ADC will be P4.7 A6
//
// SI Pin will be P5.5 A0
//
// CLK Pin will be P5.4 A1//
//

// line stores the current array of camera data


static char str[100];

// ADC_In() gets the latest value from the ADC
// ADC will be P4.7 A6

// SI Pin will be P5.5 A0

// CLK Pin will be P5.4 A1

// main

/////////////////////////////////////////////////////
//
// INIT_Camera function
//
//
/////////////////////////////////////////////////////
void INIT_Camera(void)
{
	g_sendData = FALSE;
	ControlPin_SI_Init();
	ControlPin_CLK_Init();
	ADC0_InitSWTriggerCh6();
}


/////////////////////////////////////////////////////
//
// main function
//
//
/////////////////////////////////////////////////////
int main(void)
{
    LED1_Init();
	LED2_Init();
    
    SERVO_PWM_Init();
    
    initMotor();
    
    
	int i = 0;
	//initializations
	DisableInterrupts();
	uart0_init();
    uart2_init();
	uart0_put_string("\r\nLab5 CAMERA demo\r\n");

	
	uart0_put_string("\r\nINIT LEDs\r\n");
	
	// remember that we double the desired frequency because we need to account
	// for the toggle from hi to low.
	//

	uart0_put_string("\r\nINIT Camera CLK and SI\r\n");
	uart0_put_string("\r\nINIT ADC\r\n");	
	INIT_Camera();
	
	uart0_put_string("\r\nINIT Switch 2\r\n");
	Switch2_Init();


	uart0_put_string("\r\nEnable Interrupts\r\n");
	EnableInterrupts();
	uart0_put_string("\r\nInterrupts successfully enabled\r\n");
    
    //int angle = 0;
    int turn = 0;

	while(1)
	{
        
        
        
        //SERVO_ANGLE(angle);
        //angle %= 100;
        //angle += 10;
        if (g_sendData == TRUE) 
		{

            
			// send the array over uart
			//sprintf(str,"%i\n\r",-1); // start value
			//uart0_put_string(str);
            int minVal = (line[0]+line[1]+line[2])/3;
            int minDex = 0;
            
            int minLeft = minVal;
            int minDexLeft = 0;
            
            int minRight = (line[125]+line[126]+line[127])/3;
            int minDexRight = 127;
            int smoothed[128];
            
			for (i = 0; i < 128; i++) 
			{
                //sprintf(str,"%i\n\r", line[i]);
				//uart0_put_string(str);
                
                switch(i)
                {
                    case 0:
                        smoothed[i] = (line[i]+line[i+1]+line[i+2])/3;
                        break;
                    
                    case 1:
                        smoothed[i] = (line[i-1]+line[i]+line[i+1]+line[i+2])/4;
                        break;
                    
                    case 126:
                        smoothed[i] = (line[i+1]+line[i]+line[i-1]+line[i-2])/4;
                        break;
                    
                    case 127:
                        smoothed[i] = (line[i]+line[i-1]+line[i-2])/3;
                        break;
                    
                    default:
                        smoothed[i] = (line[i-2]+line[i-1]+line[i]+line[i+1]+line[i+2])/5;
                        break;
                }
                
                if (smoothed[i] < minVal)
                {
                    minVal = smoothed[i];
                    minDex = i;
                }
                
                if ((i <= 63) && (smoothed[i] < minLeft))
                {
                    minLeft = smoothed[i];
                    minDexLeft = i;
                }
                else if ((i > 63) && (smoothed[i] < minRight))
                {
                    minRight = smoothed[i];
                    minDexRight = i;
                }
			}
            int diff = minVal - ((minLeft+minRight)/2);
            sprintf(str,"%i\n\r", diff); // end value
			uart0_put_string(str);

            
            if (diff == 0)
            {
                SERVO_12OCLOCK();
                setLeftMotorSpeed(SLOW_SPEED);
                setRightMotorSpeed(SLOW_SPEED);
            }
            else if (minDex <= 63)
            {                
                if(minDex == 0)
                {
                    if (turn == 0)
                    {
                        if (minDexRight < 127)
                        {
                            SERVO_12OCLOCK();
                            setLeftMotorSpeed(FAST_SPEED);
                            setRightMotorSpeed(FAST_SPEED);
                        }
                        else
                        {
                            SERVO_12OCLOCK();
                            setLeftMotorSpeed(FAST_SPEED);
                            setRightMotorSpeed(FAST_SPEED);
                        }
                    }
                    else
                    {
                        SERVO_3OCLOCK();
                        setLeftMotorSpeed(FAST_TURN_SPEED);
                        setRightMotorSpeed(SLOW_TURN_SPEED);
                    }
                }
                else
                {
                    SERVO_ANGLE(70);
                    turn = 1;
                    setLeftMotorSpeed(SLOW_SPEED);
                    setRightMotorSpeed(SLOW_SPEED);
                }
            }
            else if (minDex > 63)
            {
                if (minDex == 127)
                {
                    SERVO_ANGLE(0);
                    setLeftMotorSpeed(SLOW_TURN_SPEED);
                    setRightMotorSpeed(FAST_TURN_SPEED);
                }
                else
                {
                    turn = 0;
                    SERVO_12OCLOCK();
                    setLeftMotorSpeed(FAST_SPEED);
                    setRightMotorSpeed(FAST_SPEED);
                }
            }
            
            
            if (minDexLeft == 0)
            {
                LED1_Off();
            }
            else if (minDexLeft <= 63)
            {
                LED1_On();
            }
            
            if ((minDexLeft == 0) && (minDexRight == 127) && (minDex == 0))
            {
                LED2_Green();
            }
            else if (minDexRight == 127)
            {
                LED2_Off();
            }
            else if (minDexRight > 63)
            {
                LED2_Cyan();
            }

            //SERVO_ANGLE(minDex);
            
            if ((minDex > 0) && (minDex < 127))
            {
                //setLeftMotorSpeed((((abs(minDex-63))*100)/64)); 
                //setRightMotorSpeed((((abs(minDex-63))*100)/64));
            }
                
            
            //sprintf(str,"M: %i\tL: %i\tR: %i\n\r",minDex,minDexLeft, minDexRight); // end value
			//uart0_put_string(str);

			g_sendData = FALSE;
		}
		// do a small delay
		//myDelay(0);
        
        
	}
}
