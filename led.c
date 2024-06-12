
#include "msp.h"
#include "led.h"
#include <stdio.h>

void LED1_Init(void)
{
	// configure PortPin for LED1 as port I/O 
	PORT_LED1->SEL0 &= ~PIN_LED1;
	PORT_LED1->SEL1 &= ~PIN_LED1;

	// make built-in LED1 LED high drive strength
	PORT_LED1->DS |= PIN_LED1;

	// make built-in LED1 out	 
	PORT_LED1->DIR |= PIN_LED1;

	// turn off LED
	LED1_Off();
}

void LED2_Init(void)
{
	// configure PortPin for LED2 as port I/O 
	PORT_LED2->SEL0 &= ~PIN_LED2_RED;
	PORT_LED2->SEL1 &= ~PIN_LED2_RED;
	
	PORT_LED2->SEL0 &= ~PIN_LED2_GREEN;
	PORT_LED2->SEL1 &= ~PIN_LED2_GREEN;
	
	PORT_LED2->SEL0 &= ~PIN_LED2_BLUE;
	PORT_LED2->SEL1 &= ~PIN_LED2_BLUE;

	// make built-in LED2 LEDs high drive strength
	PORT_LED2->DS |= PIN_LED2_RED;
	PORT_LED2->DS |= PIN_LED2_GREEN;
	PORT_LED2->DS |= PIN_LED2_BLUE;

	// make built-in LED2 out	 
	PORT_LED2->DIR |= PIN_LED2_RED;
	PORT_LED2->DIR |= PIN_LED2_GREEN;
	PORT_LED2->DIR |= PIN_LED2_BLUE;

	// turn off LED
	PORT_LED2->OUT &= ~PIN_LED2_RED;
	PORT_LED2->OUT &= ~PIN_LED2_GREEN;
	PORT_LED2->OUT &= ~PIN_LED2_BLUE;
}

void LED1_Off(void)
{
	PORT_LED1->OUT &= ~PIN_LED1;
}

void LED1_On(void)
{
	PORT_LED1->OUT |= PIN_LED1;
}

int LED1_State(){
	if ((PORT_LED1->OUT & PIN_LED1) == TRUE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

/* LED2_Sel(char ctl, char* outStr, size_t len)
   Sets the LED2 to the desired color

    inputs:  ctl     - character representing selection
             len     - size of the outStr string

    outputs: outStr  - string containing the resulting
                       color or message

    returns: 0 - success
             1 - invalid input
*/
int LED2_Sel(char ctl, char* outStr, size_t len)
{
    switch(ctl)
    {								
			  case 0: case'0': case 'o': case 'O':
            LED2_Off();
            snprintf(outStr, len, "OFF\r\n");
            break;

        case 1: case '1': case 'r': case 'R':
            LED2_Red();
            snprintf(outStr, len, "RED\r\n");
            break;

        case 2: case '2': case 'b': case 'B':
            LED2_Blue();
            snprintf(outStr, len, "BLUE\r\n");
            break;

        case 3: case '3': case 'g': case 'G':
            LED2_Green();
            snprintf(outStr, len, "GREEN\r\n");
            break;
        
        case 4: case '4': case 'c': case 'C':
            LED2_Cyan();
            snprintf(outStr, len, "CYAN\r\n");
            break;
        
        case 5: case '5': case 'm': case 'M':
            LED2_Magenta();
            snprintf(outStr, len, "MAGENTA\r\n");
            break;
        
        case 6: case '6': case 'y': case 'Y':
            LED2_Yellow();
            snprintf(outStr, len, "YELLOW\r\n");
            break;
        
        case 7: case '7': case 'w': case 'W':
            LED2_White();
            snprintf(outStr, len, "WHITE\r\n");
            break;

        default:
            snprintf(outStr, len, "INVALID INPUT\r\n");
            return 1;
    }
    
    return 0;
}

//--------LED 2 Color Functions--------
// Light LEDs to make the desired colors
void LED2_Off(void)
{
	PORT_LED2->OUT &= ~PIN_LED2_RED;
	PORT_LED2->OUT &= ~PIN_LED2_GREEN;
	PORT_LED2->OUT &= ~PIN_LED2_BLUE;
}

void LED2_Red(void)
{
	PORT_LED2->OUT |= PIN_LED2_RED;
	PORT_LED2->OUT &= ~PIN_LED2_GREEN;
	PORT_LED2->OUT &= ~PIN_LED2_BLUE;
}

void LED2_Green(void)
{
	PORT_LED2->OUT &= ~PIN_LED2_RED;
	PORT_LED2->OUT |= PIN_LED2_GREEN;
	PORT_LED2->OUT &= ~PIN_LED2_BLUE;
}

void LED2_Blue(void)
{
	PORT_LED2->OUT &= ~PIN_LED2_RED;
	PORT_LED2->OUT &= ~PIN_LED2_GREEN;
	PORT_LED2->OUT |= PIN_LED2_BLUE;
}

void LED2_Cyan(void)
{
	PORT_LED2->OUT &= ~PIN_LED2_RED;
	PORT_LED2->OUT |= PIN_LED2_GREEN;
	PORT_LED2->OUT |= PIN_LED2_BLUE;
}

void LED2_Magenta(void)
{
	PORT_LED2->OUT |= PIN_LED2_RED;
	PORT_LED2->OUT &= ~PIN_LED2_GREEN;
	PORT_LED2->OUT |= PIN_LED2_BLUE;
}

void LED2_Yellow(void)
{
	PORT_LED2->OUT |= PIN_LED2_RED;
	PORT_LED2->OUT |= PIN_LED2_GREEN;
	PORT_LED2->OUT &= ~PIN_LED2_BLUE;
}

void LED2_White(void)
{
	PORT_LED2->OUT |= PIN_LED2_RED;
	PORT_LED2->OUT |= PIN_LED2_GREEN;
	PORT_LED2->OUT |= PIN_LED2_BLUE;
}
