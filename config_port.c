/*
 * CFile1.c
 *
 * Created: 20/09/2018 11:07:52 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"
#include "config_port.h"
// Slave configuration
void portInit( ) {
	//PROPERTIES: pin configuration and peripheral function
	portProps( 0, PIN_PA08, 0x3, PORT_PMUX_PMUXE_C ); //MOSI
	portProps( 0, PIN_PA11, 0x1, PORT_PMUX_PMUXO_C ); //MISO
	portProps( 0, PIN_PA09, 0x3, PORT_PMUX_PMUXO_C ); //SCK
	portProps( 0, PIN_PA10, 0x3, PORT_PMUX_PMUXE_C ); //_SS
	portProps( 0, PIN_PA14, 0x0, PORT_PMUX_PMUXE_A ); //Pin 2
	portProps( 0, PIN_PA27, 0x0, 0); //Tx LED
	//DIRECTION: data flow as input or output
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA08 ); //input
	portDir( 0, PORT_DIRSET_OFFSET, PORT_PA11 ); //output
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA09 ); //input
	portDir( 0, PORT_DIRCLR_OFFSET, PORT_PA10 ); //input
	portDir( 0, PORT_DIRSET_OFFSET, PORT_PA27 ); //output
	//DATAOUTPUT: data logic level for output
	portOut( 0, PORT_OUTSET_OFFSET, PORT_PA10 ); //_SS to high
	portOut( 0, PORT_OUTSET_OFFSET, PORT_PA27 ); // Tx On

}

void portProps( uint8_t group, uint8_t pin, uint8_t value, uint8_t type ) {
	//GROUP: PuertoA = 0, PIN position = PINCFG register
	PORT->Group[ group ].PINCFG[ pin ].reg = value; //configuration
	//PERIPHERAL FUNCTION if needed
	if( PORT->Group[ group ].PINCFG[ pin ].bit.PMUXEN == 1 ) {
		pin = ( pin >> 1 ); //obtain MUX register
		PORT->Group[ group ].PMUX[ pin ].reg |= type; //odd or even
	}
}

void portDir( uint32_t group, uint32_t offset, uint32_t value ) {
	if( offset == PORT_DIRSET_OFFSET ) {
		PORT->Group[ group ].DIRSET.reg = value; //output direction
	} else if( offset == PORT_DIRCLR_OFFSET ) {
		PORT->Group[ group ].DIRCLR.reg = value; //input direction
	}	
}

void portOut( uint32_t group, uint32_t offset, uint32_t value ) {
	if( offset == PORT_OUTSET_OFFSET ) {
		PORT->Group[ group ].OUTSET.reg = value; //logic level "1"
		} else if( offset == PORT_OUTCLR_OFFSET ) {
		PORT->Group[ group ].OUTCLR.reg = value; //logic level "0"
	}
}