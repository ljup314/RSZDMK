/**
 * @file main.c
 * @version 1.0
 * @brief Logovanje
 * @author ljup
 * @date 15.5.2021.
 */

/// Biblioteka koja omogucava delay
#include <util/delay.h>

/// Biblioteka koja omogucava citanje integer tipova
#include <stdint.h>

/// Biblioteka sa funkcijama za koriscenje stringova
#include <stdlib.h>

/// Biblioteka za serijsku komunikaciju
#include "../usart/usart.h"

int8_t user[] = "ljup"; // Pravimo niz karaktera za username; unapred predefinisan
int8_t pass[] = "jej"; // Niz karaktera za password; unapred predefinisan

int main()
{

	int8_t usinput[64]; // Username koji unosimo
	int8_t pasinput[64]; // Password koji unosimo
	uint8_t duzime;
	uint8_t duzloz;
	int8_t indikator = 1;

	usartInit(9600);

	while(1)
	{
		indikator = 1;

		/**
		 * usartPutString() - fja koja ispisuje na serijskom izlazu string
		 * @param - string koji unosimo
		 * @return nema povratnu vrednost
		 */

		usartPutString("Unesite korisnicko ime: ");
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzime = usartGetString(usinput);
		usartPutString(usinput);
		usartPutString("\r\n");
		usinput[duzime] = '\0';

		usartPutString("Unesite lozinku: ");
		while(!usartAvailable())
			;
		_delay_ms(100);

		duzloz = usartGetString(pasinput);
		usartPutString(pasinput);
		usartPutString("\r\n");
		pasinput[duzloz] = '\0';

		if(duzime != strlen(user) || duzloz != strlen(pass))
		{
			indikator = 0;
		}
		else
		{
			for(int8_t i = 0; i < strlen(usinput); i++)
			{
				if(usinput[i] != user[i] || pasinput[i] != pass[i])
					indikator = 0;
			}
		}
		if(indikator == 0)
		{
			usartPutString("Logovanje neuspesno.");
			usartPutString("\r\n");
		}
		else
		{
			usartPutString("Dobrodosao/la, ");
			usartPutString(user);
			usartPutString("\r\n");
		}

	}
	return 0;
}
