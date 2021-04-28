#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= 1 << 5; //PB5 je izlaz

	while(1){
		PORTB |= 1 << 5; //LED ON
		_delay_ms(1000);
		PORTB &= ~(1 << 5); //LED OFF
		_delay_ms(1000);
	}

	return 0;

	}
