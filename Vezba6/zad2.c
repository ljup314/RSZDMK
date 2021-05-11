/**
 * @file v6zad2.c
 * @author Ljubica Potrebic
 * @version 1.0
 * @brief vezba 6 rszdmk zadatak 2
 * @date 11.5.2021.
 */

#include <util/delay.h>
#include <stdint.h> //Da bi program mogao da prepozna int8_t tipove podataka
#include "../usart/usart.h" // Vracamo se fajl unazad i trazimo nama potrebnu biblioteku

int main()
{
	int8_t staro[64]; // Prvobitna rec koja ne mora biti kapitalizovana
	int8_t novo[64]; // Novodobijena kapitalizovana rec
	int8_t slovo; // Proveravacemo svako slovo reci da li je malo ili veliko
	uint8_t duzina; // Prvo cemo proveriti duzinu svake reci

	usartInit(9600); // Inicijalizacija serijske komunikacije, prosledjuje se baud rate

	// Baud rate - brzina serijske komunikacije

	while(1)
	{
		usartPutString("Unesite string: ");

		while(!usartAvailable())
			;
		// Ako usartAvailable vraca nenultu vrednost, znaci da imamo neke pristigle podatke
		_delay_ms(100);



		duzina = usartGetString(staro); // Prebrojavamo koliko string ima slova
		usartPutString(staro);
		staro[duzina] = '\0'; // Kad smo prebrojali, anuliramo rec da bismo kasnije mogli napisati novu

		for(slovo = 0; slovo < duzina; slovo++)
		{
			if(staro[slovo] > 96 && staro[slovo] < 123)
				novo[slovo] = staro[slovo] - 32;
			else
				novo[slovo] = staro[slovo];
		}

		usartPutString("Dobijena rec: ");
		novo[duzina] = 0;
		usartPutString(novo);
		usartPutString("\r\n");

	}

	return 0;
}