/*
 * config_EIC.c
 *
 * Created: 31-Oct-18 11:07:52 AM
 *  Author: Antonio Arrambide
 */ 

#include "sam.h"
#include "config_EIC.h"

//void eicInit() 
//{
	// 7-2 Reserved, EIC = 1 enabled, RESET =0 disabled
//}

void eicnvic()
{
	eicCONFIG();
}
void eicCONFIG( uint32_t value) 
{
	EIC->CONFIG[1].reg |= value;
}