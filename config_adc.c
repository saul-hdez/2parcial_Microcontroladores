/*
 * config_adc.c
 *
 * Created: 08/10/2018 09:41:03 p. m.
 *  Author: Asus X556U
 */ 

#include "sam.h"
#include "config_adc.h"

void adcInit( void ) {
	adcREFCTRL( NULL, ADC_REFCTRL_REFSEL_AREFA_Val  );
	adcAVGCTRL( NULL, ADC_AVGCTRL_SAMPLENUM_1_Val );
	adcCTRLB( NULL, ADC_CTRLB_RESSEL_10BIT_Val, NULL, 1, 0, NULL );
	adcINPUTCTRL( ADC_INPUTCTRL_GAIN_1X_Val, NULL, NULL, ADC_INPUTCTRL_MUXNEG_IOGND_Val, ADC_INPUTCTRL_MUXPOS_PIN10_Val );
}

void adcREFCTRL( uint8_t ref_compensation, uint8_t ref_sel ) {
	ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL( ref_sel );
	ADC->REFCTRL.bit.REFCOMP |= ref_compensation;
}

void adcAVGCTRL( uint8_t adjust_res, uint8_t num_samples ) {
	ADC->AVGCTRL.reg = ADC_AVGCTRL_ADJRES( adjust_res ) | ADC_AVGCTRL_SAMPLENUM( num_samples );
}

void adcCTRLB( uint16_t prescaler, uint16_t resolution, uint16_t correction, uint16_t mode,
               uint16_t adjust, uint16_t differential ) {
	ADC->CTRLB.reg = ADC_CTRLB_PRESCALER( prescaler ) | ADC_CTRLB_RESSEL( resolution );
	ADC->CTRLB.bit.CORREN |= correction;  
	ADC->CTRLB.bit.FREERUN |= mode;
	ADC->CTRLB.bit.LEFTADJ |= adjust;
	ADC->CTRLB.bit.DIFFMODE |= differential;			   
}

void adcINPUTCTRL( uint32_t gain, uint32_t in_offset, uint32_t in_scan, uint32_t neg_mux,
                   uint32_t positive_mux ) {
	ADC->INPUTCTRL.reg = ADC_INPUTCTRL_GAIN( gain ) | ADC_INPUTCTRL_INPUTOFFSET( in_offset )
				       | ADC_INPUTCTRL_INPUTSCAN( in_scan ) | ADC_INPUTCTRL_MUXNEG( neg_mux )
					   | ADC_INPUTCTRL_MUXPOS( positive_mux );
}