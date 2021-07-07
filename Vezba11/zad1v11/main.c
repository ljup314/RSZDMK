#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "../PLS7/PLS7.h"
#include "../PLS7/PLS7.c"


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


const uint8_t simboli[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};

int main()
{
	init();

	uint8_t pozicija = 1; //inicijalizujemo da se nalazimo na prvom displeju
	uint8_t broj = 0; //broj koji se ocitava je nula i to je inicijalno stanje
	uint8_t tr_stanje, pr_stanje;

	pr_stanje = ocitajTaster();
	if(pr_stanje = 5)
		writeDisplay(pozicija, simboli[broj]);

	while(1)
	{
		writeDisplay(LEDS, readSwitches()); //ocitavamo ako smo ukljucili neki prekidac
		_delay_ms(50); //ceka se ocitavanje

		tr_stanje = ocitajTaster();
		if(tr_stanje != pr_stanje)
		{
			pr_stanje = tr_stanje;

			if(tr_stanje == 1) //pritisnuli smo levi taster
			{
				pozicija--;
				if(pozicija == 0)
					pozicija = 4;
				readDisplay(pozicija);
			}
			else if(tr_stanje == 2)
			{
				if(broj == 0)
					broj = 9;
				else
					broj--;
				writeDisplay(pozicija, simboli[broj]);
			}
			else if(tr_stanje == 3)
			{
				pozicija++;
				if(pozicija == 5)
					pozicija = 1;
				readDisplay(pozicija);
			}
			else if(tr_stanje == 4)
			{
				broj++;
				if(broj == 10)
					broj = 0;
				writeDisplay(pozicija, simboli[broj]);
			}

		}


	}
	return 0;
}
