/*
 * ad_converter.c
 *
 * Created: 08/10/2018 10:44:03 p. m.
 *  Author: Asus X556U
 */ 

#include "sam.h"
#include "ad_converter.h"

void adcEnable( void ) {
	if( ADC->INPUTCTRL.bit.MUXPOS == ADC_INPUTCTRL_MUXPOS_TEMP_Val )
		adcSampling( 0x3F ); //maximum sampling time when temperature sensor is selected
	ADC->CTRLA.reg |= ADC_CTRLA_ENABLE; //ADC enable
	while( ADC->STATUS.bit.SYNCBUSY ){ } //wait until I2C is enabled
}

uint16_t adcResult( ) {
	adcFlush( ); //flush the ADC pipeline to restart a new conversion
	while( !ADC->INTFLAG.bit.RESRDY ) { } //wait until the conversion is ended
	uint16_t temp = ADC->RESULT.reg; //read the ADC conversion value
	while( ADC->STATUS.bit.SYNCBUSY ){ } //wait until read synchronization is ready
	return temp; //return the ADC conversion value
}

void adcFlush( ) {
	ADC->SWTRIG.bit.FLUSH |= 1;
	while( ADC->SWTRIG.bit.FLUSH ) { } //wait until flush is done
}

void adcSampling( uint8_t samp_time  ) {
	ADC->SAMPCTRL.reg = ADC_SAMPCTRL_SAMPLEN( samp_time );
}