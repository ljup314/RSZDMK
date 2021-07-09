#include "pls7.h"
#include <util/delay.h>
#include <stdint.h>

const uint8_t decimal[] = {0x05, 0xdd, 0x46, 0x54, 0x9c, 0x34, 0x24, 0x5d, 0x04, 0x14};

typedef enum state_t {UNOS, PROVERA, PROST, NIJE} state_t; //preimenovali smo enum state_t u state_t

void ispisiNaDisp(uint8_t broj)
{
	writeDisplay(D4, decimal[broj%10]); //pisemo jedinicu
	writeDisplay(D3, decimal[(broj/10)%10]); //pisemo deseticu
	writeDisplay(D2, decimal[(broj/100)%10]); //pisemo stotinu
}
uint8_t delilac;

uint8_t prostBroj(uint8_t broj)
{
	uint8_t brojac = 0;
	for(delilac = 2; delilac < broj; delilac++)
	{
		if(broj%delilac == 0)
		{
			brojac++;
		}

	}
	if(brojac == 0)
		return 1; //broj je prost
	else
		return 2; //broj nije prost
}

int16_t main()
{
	init();
	state_t state = UNOS;
	uint8_t broj, prov;
	
	while(1)
	{

		
		switch(state)
		{
			case UNOS:
				broj = ~readSwitches();
				if(broj == 0)
				{
					ispisiNaDisp(broj);
					state = NIJE;
				}
				else if(broj == 1)
				{
					ispisiNaDisp(broj);
					state = PROST;
				}
				else
				{
					ispisiNaDisp(broj);
					state = PROVERA;
				}
			break;
			case PROVERA:
				prov = prostBroj(broj);
				writeDisplay(LEDS, 0x00); //sve diode se ukljucuju na nulu
				_delay_ms(1000); //da bi se video prelaz sa provere na sledece stanje
				if(prov == 1)
					state = PROST;
				else if(prov == 2)
					state = NIJE;
			break;
			case PROST:
				writeDisplay(LEDS, 0x7e);
				_delay_ms(1000);
				state = UNOS;
				
			break;
			case NIJE:
				writeDisplay(LEDS, 0xe7);
				_delay_ms(1000);
				state = UNOS;
			break;
		}
	}
	return 0;
}