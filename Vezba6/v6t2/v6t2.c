/**
 * @file v6t2.c
 * @author ljup
 * @brief kapitalizacija
 * @version 1.0
 * @date 13.5.2021.
 */

#include <util/delay.h>
#include "../usart/usart.h"

int main()
{
	int8_t str[64];
	int8_t novstr[64];
	uint8_t duzina;
	int8_t slovo;
	usartInit(9600);

	while(1)
	{
		usartPutString("Unesite neki string: \r\n");
		while(!usartAvailable())
			;
		_delay_ms(100);


		duzina = usartGetString(str); // Konverzija stringa u broj
		usartPutString(str);
		str[duzina] = '\0';

		for(slovo = 0; slovo < duzina; slovo++)
		{
			if(str[slovo] > 96 && str[slovo] < 123)
				novstr[slovo] = str[slovo] - 32;
			else
				novstr[slovo] = str[slovo];
		}

		usartPutString("Novodobijena rec: ");
		novstr[duzina] = 0;
		usartPutString(novstr);
		usartPutString("\r\n");
	}
	return 0;
}


