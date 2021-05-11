#include <util/delay.h>
#include "../usart/usart.h" // includovanje staticke biblioteke preko relativne putanje


int main()
{
	int8_t str[64]; // pravimo 64bajtni niz za string koji prosledjujemo getString fji
	usartInit(9600); // inicijalizujemo serijsku komunikaciju, prosledjuje se baud rate

	while(1)
	{
		usartPutString("Unesite svoje ime: \r\n"); // za novi red, posto koristimo windows, moramo da pisemo \r\n
		while (!usartAvailable())
			; // imamo praznu petlju pa zato ide ; u sledeci red
		// proveravamo da li fja usartAvailable vraca neku nenultu vrednost
		// ako vrati neku nenultu vrednost znaci da su pristigli neki podaci
		_delay_ms(100); // treba nam mali delay da bismo bili sigurni da je ceo podatak pristigao

		usartGetString(str); // ucitavanje stringa

		usartPutString("Zdravo, ");
		usartPutString(str);
		usartPutString(" :) \r\n");
	}

	return 0;
}
