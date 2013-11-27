/*
 * switch.h
 *
 * Created: 04.11.2013 12:14:53
 *  Author: Dante999
 */ 


#ifndef SWICH_H_
#define SWICH_H_

extern int switch_press[6];



 /************************************************************************
 * /brief   Initialisierung der Taster K1-K6
 *          - Setzen der IO's
 *          - Konfigurieren des Interrupts (INT1)
 *
 * /param   none
 *
 * /return  none
 *
 *
 ************************************************************************/
 void init_switch(void);


   /************************************************************************
 * /brief   ADC Messung der Taster
 *
 * /param   none
 *
 * /return  ADC Wert (uint16_t)
 *
 *
 ************************************************************************/
 uint16_t get_switch_adc(void);









#endif /* SWICH_H_ */