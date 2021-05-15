/**
 * @file v6z4.c
 * @version 1.0
 * @brief konvertovanje decimalnog broja u heksadecimalni
 * @author ljup
 * @date 15.5.2021.
 */

#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>
#include "../usart/usart.h"

void ConvertToHex(int8_t *s, uint16_t num) // Prosledjujemo string u koji cemo smestiti konvertovan broj i prosledjujemo broj koji konvertujemo
{
	uint16_t temp = num; // U temp se smesta broj koji konvertujemo u HEX
	uint8_t index = 0; // Pozicija novodobijene HEX cifre

	while(temp > 0)
	{
		if(temp % 16 < 10)
			s[index] = temp % 16 + '0'; // Kalibrisemo se u odnosu na nulu u ASCII
		else
			s[index] = temp % 16 - 10 + 'A'; // Ako je temp % 16 >= 10, onda se kalibrisemo na osnovu slova A, i to tako da ne izlazimo van opsega
		temp = temp / 16; // Vrsimo dalje iteracije da bismo dobili odgovarajuci HEX broj, dakle dok ne dodjemo do nule gde je kraj algoritma
		index++; // Pri svakom prolasku kroz petlju, prelazimo na dalju cifru u HEX zapisu
	}

	// Sad se vrsi rotiranje stringa da bismo dobili pravilan zapis, a ne naopako
	for(uint8_t i = 0; i < index / 2; i++) //nov sistem rotiranja, ne mora ovako
	{
		s[i] ^= s[index - 1 - i];
		s[index - 1 - i] ^= s[i];
		s[i] ^= s[index - 1 - i];
	}

	s[index] = '\0'; // NE ZABORAVI TERMINATOR KAD PRAVIS NEKI STRING ILI NIZ!!!!!!!!

}

int main()
{
	int8_t str[64];
	uint16_t dec_num;

	usartInit(9600);

	while(1){

		usartPutString("Unesite broj koji zelite da konvertujete: \r\n");
		while(!usartAvailable())
			;
		_delay_ms(100);

		dec_num = usartParseInt(); // Na ovaj nacin izdvajamo brojeve i prosledjujemo ih da budu decimalni broj

		// sprintf(str, "0x%x\0", dec_num); vako bismo dobili hex vrednost bez mucenja ovaj ali moramo se muciti ofc

		ConvertToHex(str, dec_num); // Pozivamo fju koja ce da nam napravi hex broj
		usartPutString(str);
		usartPutString("\r\n");
	}
	return 0;
}
