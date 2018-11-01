/*
 * SPI.c
 *
 * Created: 20/09/2018 10:14:00 p. m.
 * Author : Asus X556U
 */ 
#include "sam.h"
#include "config_pm.h"
#include "config_gclk.h"
#include "config_port.h"
#include "config_sercom0.h"
#include "spi.h"

#define SIZE 2
const uint8_t send_data[ SIZE ] = { 5, 21 };
uint8_t receive_data[ SIZE ];

void delay()
{
	volatile int i=100000;
	while (!i==0)
	{
		i=i-1;
	}
}


int main( void ) 
{
	/* Declare variables */

    /* Initialize the SAM system */
    SystemInit( );
	//STEP 1. Configure PORT to define PIN properties and directions
	myPortInit( );
	//STEP 2. Configure PM to enable APBx clock for the corresponding peripheral
	myPmInit( );
	//STEP 3. Configure GCLK to enable and define clock source for the corresponding peripheral
	myGclkInit( );
	//STEP 4. Configure SERCOMx to define operating modes, pads, baud rate, character size, etc...	
	mySercom0Init( );
	//STEP 5. Enable the corresponding vector and available INTERRUPTs
	//...
	//STEP 6. Clear the peripheral FLAGs and enable the peripheral
	mySercom0Enable( );	
    while( 1 ) 
	{
		//STEP 7. Transmit and receive DATA
		//Transmit and receive all desired characters
		mySpiXchg8bit( send_data, SIZE, receive_data );
		if (receive_data[0] ==5)
		{
			myPortOut(0, PORT_OUTCLR_OFFSET, PORT_PA27 ); //Tx Off
			delay();
		}
		else 
		{
		 myPortOut(0,PORT_OUTSET_OFFSET, PORT_PA27); //Tx On
		}
    }

}
