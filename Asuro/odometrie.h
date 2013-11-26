/*
 * odometrie.h
 *
 * Created: 11.10.2013 02:38:45
 *  Author: Dante999
 */ 


#ifndef ODOMETRIE_H_
#define ODOMETRIE_H_

#define _RPM_TRIGGER 700                                // ADC Grenze zur Drehzahlerkennung    
#define _RPM_TIME 10                                    // Umdrehungen pro x*128�s

/** bereits in asuro.h definiert **/
// #define _LEFT 0
// #define _RIGHT 1



/************************************************************************
* /brief    ADC Wert der Odometrie bestimmen
*
* /param    side:    _RIGHT    Auswahl des rechten Reifens
*                    _LEFT    Auswahl des linken Reifens
*
* /return    uint16 Wert des ADCs
*
*
************************************************************************/
uint16_t get_od_adc(char side);

/************************************************************************
* /brief    Erkennung eines schwarz-wei� Wechsels der Drehzahlscheibe
*
* /param    side:   _RIGHT     Auswahl des rechten Reifens
*                   _LEFT      Auswahl des linken Reifens
*
* /return    1:     schwarz-wei� Wechsel stattgefunden
*            0:     kein schwarz-wei� Wechsel
*
************************************************************************/
uint8_t get_tick(char side);



#endif /* ODOMETRIE_H_ */