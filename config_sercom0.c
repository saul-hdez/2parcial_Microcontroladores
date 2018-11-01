/*
 * config_sercom0.c
 *
 * Created: 25/09/2018 07:43:27 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"
#include "config_sercom0.h"

void sercom0Init( ) {
	//DORD=1 lsb, TRANSFERMODE=Mode0, FORM=0x0 SPI frame, DIPO=0x0 PAD3, DOPO=0x2 PAD0,PAD1,PAD2, MODE=SPI Master operation
	sercom0CTRLA( 1, 0, 0, 0x0, 0x0, 0x2, NULL, NULL, SERCOM_SPI_CTRLA_MODE_SPI_SLAVE_Val, NULL, NULL );
	//Configure the BAUD RATE
	sercom0BAUD(38400);
	//RXEN=1 receiver enabled, MSSEN=0 hardware control disabled, CHSIZE=0x0 8BIT
	sercom0CTRLB( 1, NULL, 0, NULL, NULL, 0x0 );
}

void sercom0Enable( ) {
	SERCOM0->SPI.INTFLAG.reg = SERCOM_SPI_INTFLAG_MASK; //clear the FLAGS
	SERCOM0->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_ENABLE; //SPI enabled
	while( SERCOM0->SPI.SYNCBUSY.bit.ENABLE ){ } //wait until SPI is enabled
}

void sercom0CTRLA( uint32_t order,  uint32_t polarity, uint32_t phase, uint32_t format, uint32_t datain,  
                   uint32_t dataout, uint32_t overflow,  uint32_t standby, uint32_t mode, uint32_t enable, 
				   uint32_t reset ) {
	//Main configurations
	SERCOM0->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_MODE( mode );
	SERCOM0->SPI.CTRLA.bit.CPOL |= polarity;
	SERCOM0->SPI.CTRLA.bit.CPHA |= phase;	
	SERCOM0->SPI.CTRLA.reg |= SERCOM_SPI_CTRLA_FORM( format ) | SERCOM_SPI_CTRLA_DIPO( datain )
						   | SERCOM_SPI_CTRLA_DOPO( dataout );   
	SERCOM0->SPI.CTRLA.bit.DORD |= order;
	//Other configurations	
	SERCOM0->SPI.CTRLA.bit.IBON |= overflow;
	SERCOM0->SPI.CTRLA.bit.RUNSTDBY |= standby;
	SERCOM0->SPI.CTRLA.bit.SWRST |= reset;
	//SERCOM0 must stay disabled until all its configured
	SERCOM0->SPI.CTRLA.bit.ENABLE |= enable;
}

void sercom0BAUD( uint32_t fbaud ) {
	//Formula to calculate BAUD in synchronous operation
	uint32_t br = ( uint32_t )( SYSCTRL_SYSTEM_CLOCK / ( 2 * fbaud ) )- 1 ;
	SERCOM0->SPI.BAUD.reg = SERCOM_SPI_BAUD_BAUD( ( uint8_t )br );
}

void sercom0CTRLB( uint32_t receiver,  uint32_t mode, uint32_t hwdetect, uint32_t lowdetect, uint32_t preload,
                   uint32_t size ) {
	//Main configurations
	SERCOM0->SPI.CTRLB.reg |= SERCOM_SPI_CTRLB_CHSIZE( size );
	SERCOM0->SPI.CTRLB.bit.MSSEN |= hwdetect;
	SERCOM0->SPI.CTRLB.bit.RXEN |= receiver;
	//Other configurations
	SERCOM0->SPI.CTRLB.reg |= SERCOM_SPI_CTRLB_AMODE( mode );	
	//For slave configuration
	SERCOM0->SPI.CTRLB.bit.SSDE |= lowdetect;
	SERCOM0->SPI.CTRLB.bit.PLOADEN |= preload;
}

