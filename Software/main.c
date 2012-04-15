/**********************************************************************
* © 2006 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33EP512MU810
* Compiler:        MPLAB® C30 v3.30 or higher
* Tested On:	   dsPIC33EP512MU810 on Explorer 16 Demo board

* ADDITIONAL NOTES: 
* Small, bare bones program to guide designers with UART implementation
*  To run program, plug DB9 cable to Terminal (9600,8,N,1) - 
*	Data sent from TERMINAL END will be represented as binary equivalent
*	of ASCII on 7 LSB LEDs of HPC16 Explorer board
*
*	Data is sent from HPC16 by pressing S3 - S6.  A single letter will
*	be transmitted upon each keypress.
*
* Peripheral Library was not utilized, Bit Addressing was used in order
* to show all details involved in initialization of UART.
* 
* 
* The Processor starts with the Internal oscillator without PLL enabled and then the Clock is switched to PLL Mode.
*
**********************************************************************/

#if defined(__dsPIC33E__)
#include "p33exxxx.h"
#elif defined(__PIC24E__)
#include "p24exxxx.h"
#endif 


_FOSCSEL(FNOSC_FRC);			// Internal FRC oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF  & POSCMD_NONE);  
								// Clock Switching is enabled and Fail Safe Clock Monitor is disabled
								// OSC2 Pin Function: OSC2 is Clock Output
								// Primary Oscillator Mode: XT Crystanl


#define TRUE	1
#define FALSE	0

unsigned char S3Flag, S4Flag, S5Flag, S6Flag;

void __attribute__ ((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
	LATA = U2RXREG;
	IFS1bits.U2RXIF = 0;
}
void __attribute__ ((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
	IFS1bits.U2TXIF = 0;
}

void InitClock() {
	PLLFBD = 38;	// M = 40
	CLKDIVbits.PLLPOST = 0;	// N1 = 2
	CLKDIVbits.PLLPRE = 0;	// N2 = 2
	OSCTUN = 0;
	RCONbits.SWDTEN = 0;

// Clock switch to incorporate PLL
	__builtin_write_OSCCONH(0x01);		// Initiate Clock Switch to 
													// FRC with PLL (NOSC=0b001)
	__builtin_write_OSCCONL(0x01);		// Start clock switching
	while (OSCCONbits.COSC != 0b001);	// Wait for Clock switch to occur	

	while(OSCCONbits.LOCK != 1) {};
}

void InitUART2() {
	// This is an EXAMPLE, so brutal typing goes into explaining all bit sets

	// The HPC16 board has a DB9 connector wired to UART2, so we will
	// be configuring this port only

	// configure U2MODE
	U2MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
	//U2MODEbits.notimplemented;	// Bit14
	U2MODEbits.USIDL = 0;	// Bit13 Continue in Idle
	U2MODEbits.IREN = 0;	// Bit12 No IR translation
	U2MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
	//U2MODEbits.notimplemented;	// Bit10
	U2MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
	U2MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
	U2MODEbits.LPBACK = 0;	// Bit6 No Loop Back
	U2MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')

	U2MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
	U2MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
	U2MODEbits.STSEL = 0;	// Bit0 One Stop Bit
	
	// Load a value into Baud Rate Generator.  Example is for 9600.
	// See section 19.3.1 of datasheet.
	//  U2BRG = (Fcy/(16*BaudRate))-1
	//  U2BRG = (37M/(16*9600))-1
	//  U2BRG = 240
	U2BRG = 240;	// 40Mhz osc, 9600 Baud

	// Load all values in for U1STA SFR
	U2STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
	U2STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
	U2STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
	//U2STAbits.notimplemented = 0;	//Bit12
	U2STAbits.UTXBRK = 0;	//Bit11 Disabled
	U2STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
	U2STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
	U2STAbits.TRMT = 0;	//Bit8 *Read Only bit*
	U2STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
	U2STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
	U2STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
	U2STAbits.PERR = 0;		//Bit3 *Read Only Bit*
	U2STAbits.FERR = 0;		//Bit2 *Read Only Bit*
	U2STAbits.OERR = 0;		//Bit1 *Read Only Bit*
	U2STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

	IPC7 = 0x4400;	// Mid Range Interrupt Priority level, no urgent reason

	IFS1bits.U2TXIF = 0;	// Clear the Transmit Interrupt Flag
	IEC1bits.U2TXIE = 1;	// Enable Transmit Interrupts
	IFS1bits.U2RXIF = 0;	// Clear the Recieve Interrupt Flag
	IEC1bits.U2RXIE = 1;	// Enable Recieve Interrupts


	RPOR9bits.RP101R = 3;		//RF5 as U2TX

	U2MODEbits.UARTEN = 1;	// And turn the peripheral on

	U2STAbits.UTXEN = 1;

}

void InitPorts() {
	// S3 (portD Pin 6, chosen as trigger for sending 'M' to UART)
	// S6 (portD Pin 7, chosen as trigger for sending 'C' to UART)
	// S5 (portA Pin 7, chosen as trigger for sending 'H' to UART)
	// S4 (portD Pin 13, chosen as trigger for sending 'P' to UART)

	TRISD = 0x20C0;	// D6,7,13 inputs
	ANSELDbits.ANSD6 = 0;
	ANSELDbits.ANSD7 = 0;
	ANSELAbits.ANSA7 = 0;
	//AD1PCFGHbits.PCFG23 = 1;	// This is important.  RA7 is muxxed with AN23,
		// So we need to config the pin as DIGITAL
	
	TRISA = 0x0080;	// only 0th bit needs be output. A7 is input
	S3Flag = S4Flag = S5Flag = S6Flag = 0;	// Some Debounce Flags

	TRISFbits.TRISF5 = 0;	// RF5 output - U2TX pin
	TRISFbits.TRISF4 = 1;	// RF4 input - U2RX pin
	RPINR19bits.U2RXR = 0b1100100; // RF4 pin - RP100 assigned to U2RX function

}

void SoftwareDebounce() {
	if(PORTDbits.RD6 == FALSE) {
		if( S3Flag == FALSE ) {
			S3Flag = TRUE;
			U2TXREG = 'M';
		}
	}
	else {
		S3Flag = FALSE;
	}
	if(PORTDbits.RD7 == FALSE) {
		if( S6Flag == FALSE ) {
			S6Flag = TRUE;
			U2TXREG = 'C';
		}
	}
	else {
		S6Flag = FALSE;
	}
	if(PORTAbits.RA7 == FALSE) {
		if( S5Flag == FALSE ) {
			S5Flag = TRUE;
			U2TXREG = 'H';
		}
	}
	else {
		S5Flag = FALSE;
	}
	if(PORTDbits.RD13 == FALSE) {
		if( S4Flag == FALSE ) {
			S4Flag = TRUE;
			U2TXREG = 'P';
		}
	}
	else {
		S4Flag = FALSE;
	}
}
int main(void) {
	
	InitClock();	// This is the PLL settings

	InitUART2();	// Initialize UART2 for 9600,8,N,1 TX/RX

	InitPorts();	// LEDs outputs, Switches Inputs

	while(1) {	// The ever versatile Infinite Loop!
		SoftwareDebounce();
	}
}
