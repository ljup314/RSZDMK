/**
 * @file main.c
 * @version 1.0
 * @brief izdvajanje samoglasnika
 * @author ljup
 * @date 15.5.2021.
 */

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"

int main()
{
	int8_t str[64];
	uint8_t duzinastr;
	int8_t i;
	int8_t samogl = 0;
	int8_t tmp[64];
	int8_t indikator = 1;
	usartInit(9600);

	while(1)
	{
		indikator = 1;
		usartPutString("Unesite rec malim slovima: ");

		while(!usartAvailable())
		;
		_delay_ms(100);

		duzinastr = usartGetString(str);
		usartPutString(str);
		usartPutString("\r\n");
		str[duzinastr] = '\0';

		for(i = 0; i < duzinastr; i++)
		{
			if(str[i] > 96 && str[i] < 123)
			{
				if(str[i] == 'a')
					samogl++;
				else if(str[i] == 'e')
					samogl++;
				else if(str[i] == 'i')
					samogl++;
				else if(str[i] == 'o')
					samogl++;
				else if(str[i] == 'u')
					samogl++;
			}
			else
				indikator = 0;
		}
		if(indikator == 0)
		{
			usartPutString("Upis neuspesan. ");
			usartPutString("\r\n");
		}
		else
		{
			sprintf(tmp, "%d\0", samogl);
			usartPutString("Rec ima ");
			usartPutString(tmp);
			usartPutString(" samoglasnika.");
			usartPutString("\r\n");
			tmp[duzinastr] = '\0';
			samogl = 0;
		}
	}
	return 0;
}

