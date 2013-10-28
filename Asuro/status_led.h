/*
 * status_led.h
 *
 * Created: 08.10.2013 23:30:08
 *  Author: Dante999
 */ 


#ifndef STATUS_LED_H_
#define STATUS_LED_H_

void back_led (char left, char right);
void init_led (void);
void status_led( char colour);

/** bereits in asuro.h definiert **/
//#define _OFF	0
//#define _ON	1

#define _GREEN  1
#define _RED    2
#define _ORANGE 3

#endif /* STATUS_LED_H_ */