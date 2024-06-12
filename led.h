#include <stdio.h>

#define PORT_LED1 			P1
#define PIN_LED1				BIT0

#define PORT_LED2 			P2
#define PIN_LED2_RED 		BIT0
#define PIN_LED2_GREEN 	BIT1
#define PIN_LED2_BLUE 	BIT2

#define PORT_SW1				P1
#define	PIN_SW1					BIT1

#define PORT_SW2	P1
#define	PIN_SW2		BIT4

#ifndef BOOLEAN
typedef unsigned char BOOLEAN; 
#define FALSE 0
#define TRUE  !FALSE
#endif

void LED1_Init(void);
void LED2_Init(void);
void LED1_Off(void);
void LED1_On(void);
int LED1_State(void);
int  LED2_Sel(char ctl, char* outStr, size_t len);
void LED2_Off(void);
void LED2_Red(void);
void LED2_Green(void);
void LED2_Blue(void);
void LED2_Cyan(void);
void LED2_Magenta(void);
void LED2_Yellow(void);
void LED2_White(void);
