/*
 * config_EIC.h
 *
 * Created: 31-Oct-18 11:08:19 AM
 *  Author: Antonio Arrambide
 */ 

#ifndef CONFIG_EIC_H_
#define CONFIG_EIC_H_

void eicInit();

void eicCTRL();
void eicnvic();
void eicCONFIG();

	

#define myEicInit eicInit

#endif /* CONFIG_EIC_H_ */
