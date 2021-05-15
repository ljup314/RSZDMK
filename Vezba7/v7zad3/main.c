/**
 * @file main.c
 * @version 1.0
 * @brief Sabiranje cifara
 * @author ljup
 * @date 15.5.2021.
 */

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"

int main()
{
	int16_t broj;
	int16_t zbir = 0;
	int8_t tmp[40], ispis[40];
	int8_t ostatak;

	usartInit(9600);

	while(1)
	{
		usartPutString("Unesite broj: ");
		while(!usartAvailable())
			;
		_delay_ms(100);

		broj = usartParseInt();
		sprintf(ispis, "%d", broj);
		usartPutString(ispis);
		usartPutString("\r\n");

		while(broj != 0)
		{
			ostatak = broj % 10; // Npr ako imamo 456, kao ostatak nam ostaje 6
			zbir += ostatak; // U zbir upisujemo 6
			broj = broj / 10; // Da bismo smanjili broj, delimo ga sa 10; ostaje 45, u sledecoj iteraciji se opet smanjuje
		}

		sprintf(tmp, "%d\0", zbir);
		usartPutString("Zbir cifara je ");
		usartPutString(tmp);
		usartPutString("\r\n");
		zbir = 0;
	}
	return 0;
}


