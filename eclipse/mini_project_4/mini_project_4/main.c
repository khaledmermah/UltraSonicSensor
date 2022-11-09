
//
#include "lcd.h"
#include "icu.h"
#include"ultrasonic.h"
#include <avr/io.h>
uint16 distance=0;
int main()
{	LCD_init();
	Ultrasonic_init();

	LCD_moveCursor(0,0);
	LCD_displayString("Distance=   cm");
	while(1)
	{
			distance=Ultrasonic_readDistance();
			/* display the dutyCycle on LCD screen */
			LCD_moveCursor(0,9);
			LCD_intgerToString(distance);
		}
	}

