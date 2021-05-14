/**
 * @file v6zad3.c
 * @version 1.0
 * @brief proverava se da li je rec palindrom ili jok
 * @author ljup
 * @date 14.5.2021.
 */

#include <util/delay.h>
#include "../usart/usart.h"

int main()
{
	int8_t uneto[64], naopako[64];
	uint8_t duzina;
	int8_t i;
	int8_t indikator = 0;

	usartInit(9600);


	while(1){
		usartPutString("Unesite string: ");

		indikator = 0;
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzina = usartGetString(uneto);
		usartPutString(uneto);
		uneto[duzina] = '\0';

		for(i = 0; i < duzina; i++)
		{
			naopako[i] = uneto[duzina - 1 - i];
			if(naopako[i] == uneto[i])
				indikator++;
		}

		if(indikator == duzina)
			usartPutString(" jeste palindrom.");
		else
			usartPutString(" nije palindrom.");
		naopako[duzina] = 0;
		usartPutString("\r\n");

	}

	return 0;
}
