/*
 * ad_converter.h
 *
 * Created: 08/10/2018 10:44:33 p. m.
 *  Author: Asus X556U
 */ 


#ifndef AD_CONVERTER_H_
#define AD_CONVERTER_H_

void adcEnable( );
uint16_t adcResult( );
void adcFlush( );
void adcSampling( uint8_t samp_time  );

#define myAdcResult adcResult
#define myAdcEnable adcEnable

#endif /* AD_CONVERTER_H_ */