/**
 * @file v6t1.c
 * @author ljup
 * @date 13.5.2021.
 * @version 1.0
 * @brief kazi caocao
 */

#include <util/delay.h>
#include "../usart/usart.h"

int main()
{
	int8_t str[64];
	usartInit(9600); // Inicijalizacija serijske komunikacije, prosledjujemo baud rate

	while(1)
	{
		usartPutString("Unesi kako se zoves: \r\n");
		while(!usartAvailable()) // Dokle god ne pristigne podatak
			;
		_delay_ms(100); // Moramo sacekati da se podatak ucita

		usartGetString(str);
		usartPutString("Caocao, ");
		usartPutString(str);
		usartPutString(". :) \r\n");


	}
	return 0;
}


