/*
 * config_gclk.h
 *
 * Created: 20/09/2018 11:45:19 p. m.
 *  Author: Asus X556U
 */ 

#ifndef CONFIG_GCLK_H_
#define CONFIG_GCLK_H_

#define NULL 0

void gclkInit( );
void gclkCLKCTRL( uint16_t lock,  uint16_t enable, uint16_t generator, uint16_t id );

#define myGclkInit gclkInit

#endif /* CONFIG_GCLK_H_ */