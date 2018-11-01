/*
 * config_sercom0.h
 *
 * Created: 25/09/2018 07:43:50 p. m.
 *  Author: Asus X556U
 */ 


#ifndef CONFIG_SERCOM0_H_
#define CONFIG_SERCOM0_H_

#define NULL 0

void sercom0Init( );
void sercom0Enable( );
void sercom0CTRLA( uint32_t order,  uint32_t polarity, uint32_t phase, uint32_t format, uint32_t datain,
                   uint32_t dataout, uint32_t overflow,  uint32_t standby, uint32_t mode, uint32_t enable,
                   uint32_t reset );
void sercom0CTRLB( uint32_t receiver,  uint32_t mode, uint32_t hwdetect, uint32_t lowdetect, uint32_t preload,
                   uint32_t size );
void sercom0BAUD( uint32_t fbaud );

#define mySercom0Init sercom0Init
#define mySercom0Enable sercom0Enable

#endif /* CONFIG_SERCOM0_H_ */