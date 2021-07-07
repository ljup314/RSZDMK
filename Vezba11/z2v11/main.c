/*
 * main.c
 *
 *  Created on: Jul 7, 2021
 *      Author: LJ
 */

#include "../PLS7/PLS7.h"
#include "../PLS7/PLS7.c"
#include <util/delay.h>

uint8_t ocitajTaster()
{
	if(buttonState(LEFT))
		return 1;
	else if(buttonState(DOWN))
		return 2;
	else if(buttonState(RIGHT))
		return 3;
	else if(buttonState(UP))
		return 4;
	return 0;
}

const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04}; //pravimo niz 0d 0 do 8

int main()
{
	init();
	uint8_t pozicija = 1; //inicijalizujemo da se prvo ocita vrednost na segmentu skroz levo
	uint8_t broj = 0; //inicijalno ce se prikazivati nula
	uint8_t tr_stanje, pr_stanje, prek;

	pr_stanje = ocitajTaster();
	if(pr_stanje == 0)
		writeDisplay(pozicija, simboli[broj]);

	while(1)
	{
		writeDisplay(LEDS, readSwitches()); //cekamo da se ukljuci neki prekidac
		_delay_ms(50);

		tr_stanje = ocitajTaster();
		if(tr_stanje != pr_stanje)
		{
			pr_stanje = tr_stanje;

			if(tr_stanje == 1)
				pozicija = 1;
			else if(tr_stanje == 2)
				pozicija = 2;
			else if(tr_stanje == 3)
				pozicija = 3;
			else if(tr_stanje == 4)
				pozicija = 4;

			prek = readSwitches();

			if(prek == 0xfe)
				broj = 8;
			else if(prek == 0xfd)
				broj = 7;
			else if(prek == 0xfb)
				broj = 6;
			else if(prek == 0xf7)
				broj = 5;
			else if(prek == 0xef)
				broj = 4;
			else if(prek == 0xdf)
				broj = 3;
			else if(prek == 0xbf)
				broj = 2;
			else if(prek == 0x7f)
				broj = 1;
			else
				broj = 0;
		}

		writeDisplay(pozicija, simboli[broj]);
		_delay_ms(50);
		writeDisplay(LEDS, readSwitches());

	}
	return 0;
}
