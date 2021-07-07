/*
 * main.c
 *
 *  Created on: Jul 7, 2021
 *      Author: LJ
 */

//konvertor binarnog broja kojeg zadajemo na prekidacu, pisemo decimalni broj na 7seg displeju

#include "../PLS7/PLS7.h"
#include "../PLS7/PLS7.c"
#include <avr/io.h>
#include <math.h>
#include <stdint.h>
#include <util/delay.h>

const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};

int main()
{
	init();

	while(1)
	{

		uint8_t d1, d2, d3 = 0;
		uint8_t suma = 0;

		writeDisplay(LEDS, readSwitches());
				_delay_ms(50);

		if(switchState(0) == 0) //switchState(sw) vraca 0 ili 1, u zavisnosti da li je nas prekidac sw iskljucen ili ukljucen respektivno
			suma += pow(2, 0);
		if(switchState(1) == 0)
			suma += pow(2, 1);
		if(switchState(2) == 0)
			suma += pow(2, 2);
		if(switchState(3) == 0)
			suma += pow(2, 3);
		if(switchState(4) == 0)
			suma += pow(2, 4);
		if(switchState(5) == 0)
			suma += pow(2, 5);
		if(switchState(6) == 0)
			suma += pow(2, 6);
		if(switchState(7) == 0)
			suma += pow(2, 7);

		if(suma > 0)
		{
			d1 = suma%10; //na cifri za jedinicu pisemo ostatak pri deljenju sume sa 10
			writeDisplay(3, simboli[d1]);

			suma = suma / 10;
			d2 = suma%10;
			writeDisplay(2, simboli[d2]);//cifra za deseticu

			suma = suma / 10;
			d3 = suma%10;
			writeDisplay(1, simboli[d3]); //cifra za stotinu
		}
		else
			writeDisplay(LEDS, 0xff); //ne ispisuje nista
	}
	return 0;
}
