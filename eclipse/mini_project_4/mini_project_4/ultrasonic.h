/*
 * ultrasonic.h
 *
 *  Created on: Oct 13, 2022
 *      Author: kMermah
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
extern uint8 g_edgeCount;
extern uint16 g_timeHigh;


 void Ultrasonic_init(void);

 void Ultrasonic_Trigger(void);

 uint16 Ultrasonic_readDistance(void);

 void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
