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
	enum state_t{LOCKED, NUM1, NUM2, UNLOCKED, BROKEN, REC1, REC2};
	enum state_t state = LOCKED; //inicijalno stanje je LOCKED

	pinSetValue(PORT_B, 5, LOW); //dioda je inicijalno iskljucena


	while(1)
	{
		while(usartAvailable == 0); //cekamo prijem podataka
		c = usartGetChar(); //prijem podataka

		switch(state)
		{
		case LOCKED:
			if(c == '1')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = NUM1;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case NUM1:
			if(c == '2')
			{
				pinSetValue(PORT_B, 5, HIGH);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, LOW);
				state = NUM2;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case NUM2:
			if(c == '3')
			{
				for(int i = 0; i < 2; i++)
				{
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
				}
				state = UNLOCKED;
			}
			else
			{
				pinSetValue(PORT_B, 5, HIGH);
				state = BROKEN;
			}
			break;
		case UNLOCKED:
			break;
		case BROKEN:
			if(c == '7')
			{
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, HIGH);
				state = REC1;
			}
			else
			{
				for(int j = 0; j < 1; j++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
				}
				state = BROKEN;
			}
			break;
		case REC1:
			if(c == '8')
			{
				pinSetValue(PORT_B, 5, LOW);
				timer0DelayMs(1000);
				pinSetValue(PORT_B, 5, HIGH);
				state = REC2;
			}
			else
			{
				for(int k = 0; k < 1; k++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
				}
				state = BROKEN;
			}
			break;
		case REC2:
			if(c =='9')
			{
				pinSetValue(PORT_B, 5, LOW);
				state = LOCKED;
			}
			else
			{
				for(int l = 0; l < 1; l++)
				{
					pinSetValue(PORT_B, 5, LOW);
					timer0DelayMs(1000);
					pinSetValue(PORT_B, 5, HIGH);
					timer0DelayMs(1000);
				}
				state = BROKEN;
			}
			break;
		}

	}
	return 0;
}

