/**
 * @file v6zad5.c
 * @version 1.0
 * @brief jednostavni kalkulator
 * @author ljup
 * @date 14.5.2021.
 */

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"

int16_t Operation(int8_t operator, uint16_t op1, uint16_t op2)
{
	int16_t res; // U ovu promenljivu cemo smestati rezultat
	switch(operator)
	{
		case '+':
			res = op1 + op2;
			break;
		case '-':
			res = op1 - op2;
			break;
		case '*':
			res = op1 * op2;
			break;
		case '/':
			if(op2 == 0)
			{
				usartPutString("Deljenje nulom nije definisano!");
				break;
			}
			else
			{
				res = op1 / op2;
				break;
			}
		default:
			res = -1;
			break;
	}

	return res;
}

int main()
{
	int8_t str[64];
	int16_t number1;
	int16_t number2;
	int8_t operator;

	usartInit(9600);

	while(1)
	{
		usartPutString("Unesite neki izraz: \r\n");
		while(!usartAvailable())
			;
		_delay_ms(100);

		number1 = usartParseInt();
		operator = usartGetChar();
		number2 = usartParseInt();

		usartPutString("Uneli ste izraz = ");
		sprintf(str, "%d %c %d = \0", number1, operator, number2);
		usartPutString(str);
		sprintf(str, "%d\0", Operation(operator, number1, number2)); // U string smestimo vrednost koju dobijemo fjom Operation()
		usartPutString(str); // Ispisemo sta smo dobili jej
		usartPutString("\r\n");
	}

	return 0;
}
