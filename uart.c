/*
 * File:        uart.c
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */

#include "msp.h"
#include "uart.h"  // you need to create this file with the function prototypes
#include <string.h>
#include "led.h"

void uart0_init()
{
	//Set the UART to RESET state (set bit0 of EUSCI_A0->CTLW0 register to '1'
	EUSCI_A0->CTLW0 |= EUSCI_A_CTLW0_SWRST; 

	// bit15=0,      no parity bits
	// bit14=x,      not used when parity is disabled
	// bit13=0,      LSB first
	// bit12=0,      8-bit data length
	// bit11=0,      1 stop bit
	// bits10-8=000, asynchronous UART mode
	// bits7-6=11,   clock source to SMCLK
	// bit5=0,       reject erroneous characters and do not set flag
	// bit4=0,       do not set flag for break characters
	// bit3=0,       not dormant
	// bit2=0,       transmit data, not address (not used here)
	// bit1=0,       do not transmit break (not used here)
	// bit0=1,       hold logic in reset state while configuring

	// set CTLW0 - hold logic and configure clock source to SMCLK
	EUSCI_A0->CTLW0 = 0x00C1; // = b0000000011000001

	// baud rate
	// N = clock/baud rate = clock_speed/BAUD_RATE
	// set BRW register
	EUSCI_A0->BRW = (SystemCoreClock/BAUD_RATE);

	 // clear first and second modulation stage bit fields
	// MCTLW register;  
	EUSCI_A0->MCTLW &= ~0xFFF1;
    
    LED2_Red();
	

	// P1.3 = TxD
	// P1.2 = RxD
	// we will be using P1.2, P1.3 for RX and TX but not in I/O mode, so we set Port1 SEL1=0 and SEL0=1
	// set SEL0, SEL1 appropriately
	PORT_UART0_RX->SEL0 |= 0x0C;
	PORT_UART0_RX->SEL1 &= ~0x0C;

	// CTLW0 register - release from reset state
	EUSCI_A0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

	// disable interrupts (transmit ready, start received, transmit empty, receive full)	
	// IE register;      
	EUSCI_A0->IE = 0x0001;
    //LED2_Green();
}

BYTE uart0_getchar(void)
{
	BYTE inChar;
	// Wait for data
	// IFG register
	while (uart0_dataAvailable() == FALSE);

	// read character and store in inChar variable
	// RXBUF register
	inChar = EUSCI_A0->RXBUF;

	//Return the 8-bit data from the receiver 
	return(inChar);

}

void uart0_putchar(char ch)
{
	// Wait until transmission of previous bit is complete 
	// IFG register
	while((EUSCI_A0->IFG & EUSCI_A_IFG_TXIFG) == 0);
	
	// send ch character to uart
	// TXBUF register 
	EUSCI_A0->TXBUF = ch;

}

void uart0_put(char *ptr_str)
{
	while(*ptr_str != 0)
		uart0_putchar(*ptr_str++);
}

BOOLEAN uart0_dataAvailable(void)
{
	BOOLEAN go = FALSE;
	
	// if a character is available, set go = TRUE
	if ((EUSCI_A0->IFG & EUSCI_A_IFG_RXIFG) != 0)
	{
		go = TRUE;
	}
return go;
}

void uart0_put_string(char *ptr_str)
{
	while(*ptr_str)
		uart0_putchar(*ptr_str++);
}

void uart0_get_string(char *get_str, int len)
{
	char inChar;
	int i = 0;
		
	while (i <= len)
	{
		inChar = uart0_getchar(); // read a character from the UART

		if (inChar == 13)
		{
			break;
		}
		
		if (inChar == 127) //Handle backspaces (because I felt like it)
		{
			if (i > 0)
			{
				uart0_putchar(inChar); 
				i --;
				get_str[i] = 0;
			}
		}
		else if (i == len)
		{
			continue;
		}
		else
		{
			get_str[i] = inChar;
			uart2_put_string(&get_str[i]);  // write the character to the UART
			i++;
		}
		
	}
}

void uart0_put_int(int in)
{
	int dec =1;
	int digit;
	char out[10] = {0};
    
    if (in < 0)
    {
        uart0_put_string("-");
    }
	
	while ((in % dec) != in)
	{
		digit = in % (dec*10);
		digit /= dec;
        if ((in >=0) || (digit == 0))
        {
            out[strlen(out)] = digit+48;
        }
        else
        {
            out[strlen(out)] = 48-digit;
        }
		dec*=10;
	}
	
	int rev;
	
    if (strlen(out)==0)
    {
        uart0_put_string("0");
    }
    else
    {
        for (rev = strlen(out)-1; rev >= 0; rev--)
        {
            uart0_putchar(out[rev]);
        }
	}
}

void uart0_put_int_hex(int in)
{
	int dec =1;
	int digit;
	char out[10] = {0};
	
	while ((in % dec) != in)
	{
		digit = in % (dec*16);
		digit /= dec;
        if (digit > 9)
        {
            out[strlen(out)] = digit+55;
        }
        else
        {
            out[strlen(out)] = digit+48;
        }
		
		dec*=16;
	}
	
	int rev;
    
    uart0_put_string("0x");
    
    if (strlen(out)==0)
    {
        uart0_put_string("0");
    }
    else
    {        
        for (rev = strlen(out)-1; rev >= 0; rev--)
        {
            uart0_putchar(out[rev]);
        }
    }
	
}

void uart0_clear_screen(void)
{
    uart0_put_string("\033[2J");
}

void uart2_init()
{
	//Set the UART to RESET state (set bit0 of EUSCI_A2->CTLW0 register to '1'
	EUSCI_A2->CTLW0 |= EUSCI_A_CTLW0_SWRST; 

	// bit15=0,      no parity bits
	// bit14=x,      not used when parity is disabled
	// bit13=0,      LSB first
	// bit12=0,      8-bit data length
	// bit11=0,      1 stop bit
	// bits10-8=000, asynchronous UART mode
	// bits7-6=11,   clock source to SMCLK
	// bit5=0,       reject erroneous characters and do not set flag
	// bit4=0,       do not set flag for break characters
	// bit3=0,       not dormant
	// bit2=0,       transmit data, not address (not used here)
	// bit1=0,       do not transmit break (not used here)
	// bit0=1,       hold logic in reset state while configuring

	// set CTLW0 - hold logic and configure clock source to SMCLK
	EUSCI_A2->CTLW0 = 0x00C1; // = b0000000011000001

	// baud rate
	// N = clock/baud rate = clock_speed/BAUD_RATE
	// set BRW register
	EUSCI_A2->BRW = (SystemCoreClock/BAUD_RATE);

	 // clear first and second modulation stage bit fields
	// MCTLW register;  
	EUSCI_A2->MCTLW &= ~0xFFF1;
	

	// P3.3 = TxD
	// P3.2 = RxD
	// we will be using P3.2, 3.3 for RX and TX but not in I/O mode, so we set Port1 SEL1=0 and SEL0=1
	// set SEL0, SEL1 appropriately
	PORT_UART2_RX->SEL0 |= 0x0C;
	PORT_UART2_RX->SEL1 &= ~0x0C;

	// CTLW0 register - release from reset state
	EUSCI_A2->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;

	// disable interrupts (transmit ready, start received, transmit empty, receive full)	
	// IE register;      
	EUSCI_A2->IE = 0x0001;
}

BYTE uart2_getchar(void)
{
	BYTE inChar;
	// Wait for data
	// IFG register
	while (uart2_dataAvailable() == FALSE);

	// read character and store in inChar variable
	// RXBUF register
	inChar = EUSCI_A2->RXBUF;

	//Return the 8-bit data from the receiver 
	return(inChar);

}

void uart2_putchar(char ch)
{
	// Wait until transmission of previous bit is complete 
	// IFG register
	while((EUSCI_A2->IFG & EUSCI_A_IFG_TXIFG) == 0);
	
	// send ch character to uart
	// TXBUF register 
	EUSCI_A2->TXBUF = ch;

}

void uart2_put(char *ptr_str)
{
	while(*ptr_str != 0)
		uart2_putchar(*ptr_str++);
}

BOOLEAN uart2_dataAvailable(void)
{
	BOOLEAN go = FALSE;
	
	// if a character is available, set go = TRUE
	if ((EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG) != 0)
	{
		go = TRUE;
	}
return go;
}

void uart2_put_string(char *ptr_str)
{
	while(*ptr_str)
		uart2_putchar(*ptr_str++);
}

void uart2_get_string(char *get_str, int len)
{
	char inChar;
	int i = 0;
		
	while (i <= len)
	{
		inChar = uart2_getchar(); // read a character from the UART

		if (inChar == '\r')
		{
			break;
		}
		
		if (inChar == 127) //Handle deletes
		{
			if (i > 0)
			{
				uart2_putchar(inChar); 
				i --;
				get_str[i] = 0;
			}
		}
		else if (i == len)
		{
			continue;
		}
		else
		{
			get_str[i] = inChar;
			uart2_put_string(&get_str[i]);  // write the character to the UART
			i++;
		}
		
	}
}
