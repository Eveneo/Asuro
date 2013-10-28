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

void init_motor(void);
void motor_dir( char left, char right);
void motor_pwr( uint8_t left, uint8_t right);



#endif /* MOTOR_CONTROL_H_ */