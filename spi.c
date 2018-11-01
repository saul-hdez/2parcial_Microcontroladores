/*
 * SPI.c
 *
 * Created: 28/09/2018 12:22:31 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"

#include "spi.h"
#include "config_port.h"

void spiXchg8bit( const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff) {
	// ssLow( ); //transaction is initiated
	//Cycle to transmit all characters
	for( uint32_t i = 0; i < bc; i++ ) {
		//The character will be transfered to shift register when empty
		spiSend8bit( *( send_buff++ ) );
		//As each character is shifted out from master, another character is shifted in from slave
		receive_buff[ i ] = spiReceive8bit( );
	}
	// ssHigh( ); //transaction is finished
}

void spiXchg9bit( const uint16_t * send_buff, uint32_t bc, uint16_t * receive_buff ) {
	ssLow( ); //transaction is initiated
	//cycle to transmit all characters
	for( uint32_t i = 0; i < bc; i++ ) {
		//The character will be transfered to shift register when empty
		spiSend9bit( *( send_buff++ ) );
		//As each character is shifted out from master, another character is shifted in from slave
		receive_buff[ i ] = spiReceive9bit( );
	}
	ssHigh( ); //transaction is finished
}

void ssLow( ) {
	myPortOut( 0, PORT_OUTCLR_OFFSET, PORT_PA10 ); //_SS to low
}

void ssHigh( ) {
	while( !SERCOM0->SPI.INTFLAG.bit.TXC ) { } //wait until the last character was transmitted
	myPortOut( 0, PORT_OUTSET_OFFSET, PORT_PA10 ); //_SS to high
}

void spiSend8bit( uint8_t temp ) {
	while( !SERCOM0->SPI.INTFLAG.bit.DRE ){ } //wait until shift register is empty
	SERCOM0->SPI.DATA.reg = SERCOM_SPI_DATA_DATA( temp ); //write character to transmit
}

void spiSend9bit( uint16_t temp ) {
	while( !SERCOM0->SPI.INTFLAG.bit.DRE ){ } //wait until shift register is empty
	SERCOM0->SPI.DATA.reg = SERCOM_SPI_DATA_DATA( temp ); //write character to transmit
}

uint8_t spiReceive8bit( ) {
	while( !SERCOM0->SPI.INTFLAG.bit.RXC ){ } //wait until receive is complete
	return SERCOM0->SPI.DATA.bit.DATA; //read character received
}

uint16_t spiReceive9bit( ) {
	while( !SERCOM0->SPI.INTFLAG.bit.RXC ){ } //wait until receive is complete
	return SERCOM0->SPI.DATA.bit.DATA; //read character received
}