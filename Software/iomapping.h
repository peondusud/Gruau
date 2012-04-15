/************************************************************************
*                                                                       *
* This redefines I/O mapping for each device family                     *
*                                                                       *
*************************************************************************
* Company:             Microchip Technology, Inc.                       *
*                                                                       *
* Software License Agreement                                            *
*                                                                       *
* The software supplied herewith by Microchip Technology Incorporated   *
* (the "Company") for its PICmicro® Microcontroller is intended and     *
* supplied to you, the Company's customer, for use solely and           *
* exclusively on Microchip PICmicro Microcontroller products. The       *
* software is owned by the Company and/or its supplier, and is          *
* protected under applicable copyright laws. All rights are reserved.   *
* Any use in violation of the foregoing restrictions may subject the    *
* user to criminal sanctions under applicable laws, as well as to       *
* civil liability for the breach of the terms and conditions of this    *
* license.                                                              *
*                                                                       *
* THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,     *
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED     *
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           *
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,     *
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR            *
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.                     *
************************************************************************/

#define BUTTON1   PORTDbits.RD6   	//S3
#define BUTTON2   PORTDbits.RD7		//S6
#define BUTTON3   PORTAbits.RA7		//S5
#define BUTTON4   PORTDbits.RD13	//S4



#if defined(__PIC24FJ64GB004__)
        //ADC input mapping
        #define AN_VOLT_PIN  	AD1PCFGbits.PCFG7			//voltage input on AN7
        #define ADC_VOLT_CHAN	7
        
        #define AN_TEMP_PIN	 	AD1PCFGbits.PCFG6 			//temp input on AN6
        #define ADC_TEMP_CHAN	6
                
        //Push Button I/O Mapping
        #define BUTTON1_IO		PORTAbits.RA10              // S3 on exp16
        #define BUTTON2_IO		PORTAbits.RA9               // S6 on exp16
        #define BUTTON3_IO		PORTCbits.RC6               // S5 on exp16
        #define BUTTON4_IO		PORTAbits.RA7               // S4 on exp16
        
        #define BUTTON1_TRIS	TRISAbits.TRISA10
        #define BUTTON2_TRIS	TRISAbits.TRISA9
        #define BUTTON3_TRIS	TRISCbits.TRISC6
        #define BUTTON4_TRIS	TRISAbits.TRISA7
        
        
        //LED I/O Mapping
	#define LED3	LATAbits.LATA9
	#define LED4	LATAbits.LATA10
	#define LED5	LATAbits.LATA11
	#define LED6	LATCbits.LATC8
	#define	LED7	LATCbits.LATC9
	#define LED8	LATBbits.LATB12
	#define LED9	LATBbits.LATB2
	#define LED10	LATBbits.LATB3

	#define TRIS_LED3	TRISAbits.TRISA9
	#define TRIS_LED4	TRISAbits.TRISA10
	#define TRIS_LED5	TRISAbits.TRISA11
	#define TRIS_LED6	TRISCbits.TRISC8
	#define	TRIS_LED7	TRISCbits.TRISC9
	#define TRIS_LED8	TRISBbits.TRISB12
	#define TRIS_LED9	TRISBbits.TRISB2
	#define TRIS_LED10	TRISBbits.TRISB3
        
        
        //SPI I/O Mapping
        #define PPS_SPI_SS_IO		LATAbits.LATA8
        #define PPS_SPI_SS_TRIS	    TRISAbits.TRISA8
        #define PPS_SPI_SCK_TRIS	TRISCbits.TRISC8
        #define PPS_SPI_SDI_TRIS	TRISCbits.TRISC4
        #define PPS_SPI_SDO_TRIS	TRISCbits.TRISC5
        
        
        //UART I/O Mapping
        #define PPS_UART2_TX_TRIS		TRISCbits.TRISC9
        #define PPS_UART2_RX_TRIS		TRISCbits.TRISC3
        
        //PPS Outputs
        #define NULL_IO		0
        #define C1OUT_IO	1
        #define C2OUT_IO	2
        #define U1TX_IO		3
        #define U1RTS_IO	4
        #define U2TX_IO		5
        #define U2RTS_IO	6
        #define SDO1_IO		7
        #define SCK1OUT_IO	8
        #define SS1OUT_IO	9
        #define SDO2_IO		10
        #define SCK2OUT_IO	11
        #define SS2OUT_IO	12
        #define OC1_IO		18
        #define OC2_IO		19
        #define OC3_IO		20
        #define OC4_IO		21
        #define OC5_IO		22
    #endif //__PIC24FJ64GB004__


