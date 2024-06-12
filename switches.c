/* 
Title: MSP432 GPIO and Keil MicroVision 
Purpose:   
Name:  Chase Lewis	 
Date: 08/27/21

This file prepared by LJBeato
01/11/2021
  
*/
#include "msp.h"
#include "Common.h"
#include "switches.h"
#include "CortexM.h"


void Switch1_Init(){
	// configure PortPin for Switch 1 and Switch2 as port I/O
	PORT_SW1->SEL0 &= ~PIN_SW1;
	PORT_SW1->SEL1 &= ~PIN_SW1;

  // configure as input
	PORT_SW1->DIR &= ~PIN_SW1;

	// enable pullup resistor
	PORT_SW1->REN |= PIN_SW1;
	PORT_SW1->OUT |= PIN_SW1;
}
void Switch2_Init(){
  // configure PortPin for Switch2 as port I/O
	PORT_SW2->SEL0 &= ~PIN_SW2;
	PORT_SW2->SEL1 &= ~PIN_SW2;

  // configure as input
	PORT_SW2->DIR &= ~PIN_SW2;

  // enable pullup resistor
	PORT_SW2->REN |= PIN_SW2;
	PORT_SW2->OUT |= PIN_SW2;
}

//------------Switch_Input------------
// Read and return the status of Switch1
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch1_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	retVal = !((PORT_SW1->IN&PIN_SW1)&& TRUE); // returns PIN_SW1 w/o && TRUE

	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}
//------------Switch_Input------------
// Read and return the status of Switch2
// Input: none
// return: TRUE if pressed
//         FALSE if not pressed
BOOLEAN Switch2_Pressed(void)
{
	BOOLEAN retVal = FALSE;
	// check if pressed
	retVal = !((PORT_SW2->IN&PIN_SW2) && TRUE);
	
	return (retVal);              // return TRUE(pressed) or FALSE(not pressed)
}

//

//  I/O interrupt pin setup
//
// DIR     SEL0/SEL1    IE    IES     Port Mode
//  0          00        0     0       Input, rising edge trigger
//  0          00        0     1       Input, falling edge trigger
//  0          00        1     0       Input, rising edge trigger, interrupt
//  0          00        1     1       Input, falling edge trigger, interrupt
//

void Switch1_Interrupt_Init(void)
{
	// disable interrupts
	DisableInterrupts();
	// initialize the Switch as per previous lab
	Switch1_Init();
		
	//7-0 PxIFG RW 0h Port X interrupt flag
	//0b = No interrupt is pending.
	//1b = Interrupt is pending.
	// clear flag1 (reduce possibility of extra interrupt)	
  PORT_SW1->IFG &= ~PIN_SW1; 

	//7-0 PxIE RW 0h Port X interrupt enable
	//0b = Corresponding port interrupt disabled
	//1b = Corresponding port interrupt enabled	
	// arm interrupt on  P1.1	
  PORT_SW1->IE |= PIN_SW1;
	
	//7-0 PxIES RW Undefined Port X interrupt edge select
  //0b = PxIFG flag is set with a low-to-high transition.
  //1b = PxIFG flag is set with a high-to-low transition
	// now set the pin to cause falling edge interrupt event
	// P1.1 is falling edge event
  PORT_SW1->IES |= PIN_SW1; 
	
	// now set the pin to cause falling edge interrupt event
  NVIC_IPR8 = (NVIC_IPR8 & 0x00FFFFFF)|0x40000000; // priority 2
	
	// enable Port 1 - interrupt 35 in NVIC	
  NVIC_ISER1 = 0x00000008;  
	
	// enable interrupts  (// clear the I bit	)
  EnableInterrupts();              
	
}
void Switch2_Interrupt_Init(void)
{
	// disable interrupts
	DisableInterrupts();
	
	// initialize the Switch as per previous lab
	Switch2_Init();
	
	// now set the pin to cause falling edge interrupt event
	// P1.4 is falling edge event
  PORT_SW2->IES |= PIN_SW2;   
  
	// clear flag4 (reduce possibility of extra interrupt)
	PORT_SW2->IFG &= ~PIN_SW2;
   
	// arm interrupt on P1.4 
	PORT_SW2->IE |= PIN_SW2;  
	
	// now set the pin to cause falling edge interrupt event
  NVIC_IPR8 = (NVIC_IPR8&0x00FFFFFF)|0x40000000; // priority 2
	
	// enable Port 1 - interrupt 35 in NVIC
  NVIC_ISER1 = 0x00000008;         
	
	// enable interrupts  (// clear the I bit	)
  EnableInterrupts();              
	
}
