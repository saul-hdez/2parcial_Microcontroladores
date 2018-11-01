/*
 * spi.h
 *
 * Created: 28/09/2018 12:23:09 p. m.
 *  Author: Asus X556U
 */ 


#ifndef SPI_H_
#define SPI_H_

void spiXchg8bit( const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff );
void spiXchg9bit( const uint16_t * send_buff, uint32_t bc, uint16_t * receive_buff );
void ssLow( );
void ssHigh( );
void spiSend8bit( uint8_t temp );
void spiSend9bit( uint16_t temp );
uint8_t spiReceive8bit( );
uint16_t spiReceive9bit( );

#define mySpiXchg8bit spiXchg8bit
#define mySpiXchg9bit spiXchg9bit

#endif /* SPI_H_ */