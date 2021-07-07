#include <avr/io.h>
#include <stdint.h>
#include "../usart/usart.c"
#include "../usart/usart.h"
#include "../pin_driver/pin.c"
#include "../pin_driver/pin.h"
#include "../timer0/timer0.c"
#include "../timer0/timer0.h"

int main()
{
	pinInit(PORT_B, 5, OUTPUT);
	timer0InteruptInit();
	usartInit(9600);

	int8_t c; //karakter koji unosimo
	enum stanje_t{CF0, OF0, CF0U, CF1, OF1, CF1D, CF1U, CF2D, OF2, CF2};
	enum stanje_t stanje = CF0;

	pinSetValue(PORT_B, 5, HIGH);

	while(1)
	{
		while(usartAvailable());
		c = usartGetChar();

		switch(stanje)
		{
		case CF0:
			for(int i = 0; i < 2; i++)
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
			}
			stanje = OF0;
			break;
		case OF0:
			if(c == 'U')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				stanje = CF0U;
			}
			else
				stanje = OF0;
			break;
		case CF0U:
			pinSetValue(PORT_B, 5, HIGH);
			stanje = CF1;
			break;
		case CF1:
			for(int j = 0; j < 2; j++)
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
			}
			stanje = OF1;
			break;
		case OF1:
			if(c == 'D')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
			    stanje = CF1D;
			}
			else if (c == 'U')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				stanje = CF1U;
			}
			else
				stanje = OF1;
			break;
		case CF1D:
			pinSetValue(PORT_B, 5, HIGH);
			stanje = CF0;
			break;
		case CF1U:
			pinSetValue(PORT_B, 5, HIGH);
			stanje = CF2;
			break;
		case CF2:
			for(int k = 0; k < 2; k++)
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
			}
			stanje = OF2;
			break;
		case OF2:
			if(c == 'D')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				stanje = CF2D;
			}
			else
				stanje = OF2;
			break;
		case CF2D:
			pinSetValue(PORT_B, 5, HIGH);
			stanje = CF1;
			break;
		}

	}
	return 0;
}
