#ifndef BOOLEAN
typedef unsigned char BOOLEAN; 
#define FALSE 0
#define TRUE  !FALSE
#endif

#define PORT_SW1				P1
#define	PIN_SW1					BIT1

#define PORT_SW2	P1
#define	PIN_SW2		BIT4

void Switch1_Init(void);
void Switch2_Init(void);
void Switch1_Interrupt_Init(void);
void Switch2_Interrupt_Init(void);
BOOLEAN Switch1_Pressed(void);
BOOLEAN Switch2_Pressed(void);
