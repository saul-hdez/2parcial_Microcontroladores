
/*
 * config_gclk.c
 *
 * Created: 20/09/2018 11:45:02 p. m.
 *  Author: Asus X556U
 */
#include "sam.h"
#include "config_gclk.h"

void gclkInit( ) {
	//WRTLOCK=0, CLKEN=1 enable, GEN=0x0 genclock0, ID=0x14 SERCOM0_CORE
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK0_Val, GCLK_CLKCTRL_ID_SERCOM0_CORE_Val ); // Clock configuration for SERCOM0
	//WRTLOCK=0, CLKEN=1 enable, GEN=0x1 genclock1, ID=0x5 EIC
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK1_Val, GCLK_CLKCTRL_ID_EIC_Val ); // Clock configuration for EIC
	//WRTLOCK=0, CLKEN=1 enable, GEN=0x2 genclock2, ID=0x1E ADC
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK2_Val, GCLK_CLKCTRL_ID_ADC_Val ); // Clock configuration for ADC
	//WRTLOCK=0, CLKEN=1 enable, GEN=0x2 genclock3, ID=0x1B TC3
	gclkCLKCTRL( NULL, 1, GCLK_CLKCTRL_GEN_GCLK3_Val, GCLK_CLKCTRL_ID_TCC2_TC3_Val ); // Clock configuration for TC3
	
}

void gclkCLKCTRL( uint16_t lock,  uint16_t enable, uint16_t generator, uint16_t id ) {
		//Main configurations
		GCLK->CLKCTRL.reg |= GCLK_CLKCTRL_ID( id ) | GCLK_CLKCTRL_GEN( generator ) | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID(TCC0_GCLK_ID); 
		GCLK->CLKCTRL.bit.CLKEN |= enable;
		//Other configurations
		GCLK->CLKCTRL.bit.WRTLOCK |= lock;
} 

void resetTCCModule(void){
	PORT->Group[0].DIRSET.reg = PORT_PA15;
	PORT->Group[0].OUTCLR.reg = PORT_PA15;
	PORT->Group[0].PINCFG[15].reg |= PORT_PINCFG_PMUXEN;
	PORT->Group[0].PMUX[4 >> 1].reg =  PORT_PMUX_PMUXO_E;
	/* reset TCC module */
	TCC0->CTRLA.reg = TCC_CTRLA_SWRST;
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_SWRST) {}
	TCC0->CTRLBCLR.reg = TCC_CTRLBCLR_DIR;     /* count up */
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_CTRLB) {}	
}

void configureTCC(void){
	/* configure the TCC device */
	TCC0->CTRLA.reg = (TCC_CTRLA_PRESCSYNC_GCLK_Val | TCC_CTRLA_PRESCALER(TCC_CTRLA_PRESCALER_DIV1024_Val));
	/* select the waveform generation mode -> normal PWM */
	TCC0->WAVE.reg = (TCC_WAVE_WAVEGEN_NPWM);
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_WAVE) {}
	/* set the selected period */
	TCC0->PER.reg = (1024 - 1);
	while (TCC0->SYNCBUSY.reg & TCC_SYNCBUSY_PER) {}
}

void pwmInit(void){
	/* start PWM operation */
	TCC0->CTRLA.reg |= (TCC_CTRLA_ENABLE);
}