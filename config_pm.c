/*
 * config_pm.c
 *
 * Created: 20/09/2018 11:20:19 p. m.
 *  Author: Asus X556U
 */ 
#include "sam.h"
#include "config_pm.h"

void pmInit() {
	//APBC clock for SERCOM0 is enabled, APBA clock for EIC is enabled
	pmAPBCMASK( PM_APBCMASK_SERCOM0 | PM_APBCMASK_ADC | PM_APBCMASK_TC3); 
	pmAPBAMASK( PM_APBAMASK_EIC);
}

void pmAPBCMASK( uint32_t value) {
	PM->APBCMASK.reg |= value;
}

void pmAPBAMASK( uint32_t value ) 
{
	PM->APBAMASK.reg |= value;
}



