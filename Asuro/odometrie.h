/*
 * odometrie.h
 *
 * Created: 11.10.2013 02:38:45
 *  Author: Dante999
 */ 


#ifndef ODOMETRIE_H_
#define ODOMETRIE_H_

#define _RPM_TRIGGER 700								// ADC Grenze zur Drehzahlerkennung	
#define _RPM_TIME 50									// Umdrehungen pro x*128µs
#define _LEFT 0
#define _RIGHT 1

void init_od(void);
uint16_t get_od_adc(char side);
uint8_t get_tick(char side);



#endif /* ODOMETRIE_H_ */