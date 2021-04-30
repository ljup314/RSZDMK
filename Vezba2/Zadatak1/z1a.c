/**
 * @file zad1a.c
 * @brief opis datoteke
 * @author Ljubica Potrebic
 * @date 30.04.2021.
 * @version 1.0
 */

#include <avr/io.h>
#include <util/delay.h>

//na 2Hz dioda se samo jednom upali i ugasi, dok na vecoj frekvenciji(16MHz) radi kako treba

int main(){
	DDRB |= 1 << 5;

	while(1){
		PORTB |= (1 << 5);
		_delay_ms(500);
		PORTB &= ~(1 << 5);
		_delay_ms(500);
	}

	return 0;
}

