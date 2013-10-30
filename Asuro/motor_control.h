/*
 * motor_control.h
 *
 * Created: 09.10.2013 01:50:38
 *  Author: Dante999
 */ 


#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_


#define _PWM_LEFT  OCR1AL
#define _PWM_RIGHT OCR1BL

#define _BRK 0
#define _FWD 1
#define _RWD 2

/************************************************************************
* /brief    Initialisierung
*            - Definieren der I/O's
*            - Stoppen des Motors
*            - Konfigurieren des PWM Timers
*
* /param    none
*
* /return   none
*
*
************************************************************************/
void init_motor(void);

/************************************************************************
* /brief    Drehrichtung der Motoren vorgeben
*
* /param    left:   _FWD -> Vorwärts
*                   _RWD -> Rücksärts
*                   _BRK -> Bremsen
*
*           right: _FWD -> Vorwärts
*                   _RWD -> Rücksärts
*                   _BRK -> Bremsen
*
* /return   none
*
*
************************************************************************/
void motor_dir( char left, char right);

/************************************************************************
* /brief    PWM Verhältnis der Motoren vorgeben
*
* /param    left:   0           (Motor stoppt)
*                   ...         ...
*                   255         (Motor vollgas)
*
*           right:  0           (Motor stoppt)
*                   ...         ...
*                   255         (Motor vollgas)
*
* /return   none
*
*
************************************************************************/
void motor_pwr( uint8_t left, uint8_t right);



#endif /* MOTOR_CONTROL_H_ */