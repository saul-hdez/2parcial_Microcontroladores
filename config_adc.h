/*
 * config_adc.h
 *
 * Created: 08/10/2018 09:41:24 p. m.
 *  Author: Asus X556U
 */ 


#ifndef CONFIG_ADC_H_
#define CONFIG_ADC_H_

#define NULL 0

void adcInit( );
void adcREFCTRL( uint8_t ref_compensation, uint8_t ref_sel );
void adcAVGCTRL( uint8_t adjust_res, uint8_t num_samples );
void adcCTRLB( uint16_t prescaler, uint16_t resolution, uint16_t correction, uint16_t mode,
               uint16_t adjust, uint16_t differential );
void adcINPUTCTRL( uint32_t gain, uint32_t positive_mux, uint32_t in_channels, uint32_t neg_in,
                   uint32_t positive_in );

#define myAdcInit adcInit

#endif /* CONFIG_ADC_H_ */