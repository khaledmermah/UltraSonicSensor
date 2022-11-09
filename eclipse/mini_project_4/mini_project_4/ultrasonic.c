/*
 * ultrasonic.c
 *
 *  Created on: Oct 13, 2022
 *      Author: kMermah
 */
#include<util/delay.h>
#include<avr/io.h>
#include"icu.h"
#include"ultrasonic.h"
#include"std_types.h"
#include"gpio.h"
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;

void Ultrasonic_init(void){

		/* Create configuration structure for ICU driver */
		Icu_ConfigType Icu_Config = {F_CPU_8,RISING};

		/* Enable Global Interrupt I-Bit */
		SREG |= (1<<7);

		/* Set the Call back function pointer in the ICU driver */
		Icu_setCallBack(Ultrasonic_edgeProcessing);

		/* Initialize ICU driver */
		Icu_init(&Icu_Config);
		GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void){
	PORTB |=(1<<5);
	_delay_us(10);
	PORTB &=~(1<<5);
}

uint16 Ultrasonic_readDistance(void){
	Ultrasonic_Trigger();
	while(g_edgeCount!=2){}
		g_edgeCount=0;
	return (g_timeHigh/57.8);
}

void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			Icu_clearTimerValue();
			/* Detect falling edge */
			Icu_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = Icu_getInputCaptureValue();
			/* Detect rising edge */
			Icu_setEdgeDetectionType(RISING);
		}

}

