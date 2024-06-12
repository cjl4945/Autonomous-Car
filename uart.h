
#ifndef __UART_H__
#define __UART_H__


#include "msp.h"

#define PORT_UART0_RX P1
#define PIN_UART0_RX BIT2

#define PORT_UART0_TX P1
#define PIN_UART0_TX BIT3

#define PORT_UART2_RX P3
#define PIN_UART2_RX BIT2

#define PORT_UART2_TX P3
#define PIN_UART0_TX BIT3

#ifndef BAUD_RATE
#define BAUD_RATE 115200      //default baud rate 
#endif

typedef unsigned char BYTE;
typedef unsigned char BOOLEAN;
#define FALSE 0
#define TRUE  !FALSE
typedef unsigned char BYTE;

extern uint32_t SystemCoreClock;  // clock rate of MCU

void uart0_init(void);
void uart0_putchar(char ch);
BYTE uart0_getchar(void);
BOOLEAN uart0_dataAvailable(void);
void uart0_put_string(char *ptr_str);
void uart0_get_string(char *get_str, int len);
void uart0_put_int(int in);
void uart0_put_int_hex(int in);
void uart0_clear_screen(void);


void uart2_init(void);
void uart2_putchar(char ch);
BYTE uart2_getchar(void);
BOOLEAN uart2_dataAvailable(void);
void uart2_put_string(char *ptr_str);
void uart2_get_string(char *get_str, int len);



#endif
