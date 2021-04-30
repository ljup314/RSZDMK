/**
 * @file v3zad.c
 * @brief Aplikacija koja implementira ogranicen broj treptanja diode
 * @author Ljubica Potrebic
 * @date 30.04.2021.
 * @version 1.0
 */

// u oviru gore file dela, file mora da se zove tacno kao c source file, u nasem slucaju v3zad.c

#include <avr/io.h>
#include <avr/interrupt.h>

/// Makro za podesavanje visoke vrednosti signala na pinu
#define HIGH 1
/// Makro za podesavanje niske vrednosti signala na pinu
#define LOW 0

/// Makro za selektovanje porta B
#define PORT_B 0
/// Makro za selektovanje porta C
#define PORT_C 1
/// Makro za selektovanje porta D
#define PORT_D 2

/// Makro za selektovanje pina na koji je povezana dioda
#define DIODE_PIN 5

///Promenljiva koja skladisti broj milisekundi proteklih od pokretanja aplikacije
volatile unsigned long ms = 0;

/**
 * pinPulse - fja koja implementira podizanje i spustanje vrednosti na pinu odgovarajucom brzinom
 * @param port - ulaz tipa unsigned char - port na kom je potrebno implementirati f-nalnost
 * @param pin - ulaz tipa unsigned char - pin na kom treba implementirati funkcionalnost
 * @param period - ulaz tipa unsigned long - perioda promene vrednosti na pinu
 * @return nema povratnu vrednost
 */
void pinPulse(unsigned char port, unsigned char pin, unsigned long period);

/**
 * pinSetValue - fja koja postavlja vrednost na pinu
 * @param port - ulaz tipa unsigned char - port na kom je pin ciju vrednost treba postaviti
 * @param pin - ulaz tipa unsigned char - pin ciju vrednost treba postaviti
 * @param value - ulaz tipa unsigned char - vrednost koju treba postaviti na pin
 * @return - nema povratnu vrednost
 */
void pinSetValue(unsigned char port, unsigned char pin, unsigned char value);

/**
 * pinInit - fja koja implementira inicijalizaciju pina
 * @param port - ulaz tipa unsigned char - port na kom je pin koji treba inicijalizovati
 * @param pin - ulaz tipa unsigned char - pin koji treba inicijalizovati
 * @param direction - ulaz tipa unsigned char - smer prema kom treba inicijalizovati pin
 * @return - nema povratnu vrednost
 */
void pinInit(unsigned char port, unsigned char pin, unsigned char direction);

/**
 * timer0DelayMs - fja koja implementira pauzu u broju milisekundi koji je prosledjen kao param
 * @param delay_length - ulaz tipa unsigned long - duzina pauze u ms
 * @return - povratna vrednost je tipa unsigned long i ima vrednost broja ms proteklih od pocetka aplikacije do trenutka izlaska iz fje
 */
unsigned long timer0DelayMs(unsigned long delay_length);

/**
 * timer0InteruptInit - fja koja inicijalizuje timer0 tkd pravi prekide svake milisekunde
 * @return - nema povratnu vrednost
 */
void timer0InteruptInit();

/**
 * main - fja koja implementira glavni deo aplikacije
 * @return - nema povratnu vrednost
 */
int main()
{
	unsigned long period = 1000; // Period jednog treptaja (1s)
	unsigned char repetitions = 5; // Broj treptaja
	int i;

	// Inicijalizacija
	pinInit(PORT_B, DIODE_PIN, OUTPUT);
	timer0InteruptInit();

	// Glavna petlja
	while(1)
	{
		// Treptanje
		for(i = 0; i < repetitions; i++)
			pinPulse(PORT_B, DIODE_PIN, period);

		//Kraj
		while(1)
			;

	}

	return 0;
}

/*******************************/

void pinPulse(unsigned char port, unsigned char pin, unsigned long period)
{
	// Poluperioda u kojoj pin ima visoku vrednost
	pinSetValue(port, pin, HIGH);
	timer0DelayMs(period / 2);

	// Poluperioda u kojoj pin ima nisku vrednost
	pinSetValue(port, pin, LOW);
	timer0DelayMs(period / 2);
	}

/****************************/

void pinSetValue(unsigned char port, unsigned char pin, unsigned char value)
{
	// Postavljanje vrednosti pina
	switch(port)
	{
	case PORT_B:
		if(value == HIGH)
			PORT_B |= 1 << pin;
		else
			PORT_B &= ~(1 << pin);
		break;

	case PORT_C:
		if(value == HIGH)
			PORT_C |= 1 << pin;
		else
			PORT_C &= ~(1 << pin);
		break;

	case PORT_D:
		if(value == HIGH)
			PORT_D |= 1 << pin;
		else
			PORT_D &= ~(1 << pin);
		break;

	default:
		break;
	}
	}
/************************/
void pinInit(unsigned char port, unsigned pin, unsigned char direction)
{
	//Inicijalizacija smera pina
	switch(port)
	{
	case PORT_B:
		if(direction == OUTPUT)
			DDRB |= 1 << pin;
		else
			DDRB &= ~(1 << pin);
		break;

	case PORT_C:
		if(direction == OUTPUT)
			DDRC |= 1 << pin;
		else
			DDRC &= ~(1 << pin);
		break;

	case PORT_D:
		if(direction == OUTPUT)
			DDRD |= 1 << pin;
		else
			DDRD &= ~(1 << pin);
		break;

	default:
		break;
	}
	}

/************************************/

unsigned long timer0DelayMs(unsigned long delay_length)
{
	unsigned long t0; // Trenutak od kog pocinjemo da racunamo pauzu

	// Implementacija pauze
	t0 = ms;
	whille((ms - t0) < delay_length)
	; // Pauza delay_length milisekundi

	return ms;
}

/****************************************/

void timer0InteruptInit()
{
	// Inicijalizacija tajmera 0 tako da perioda prekida bude 1ms
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	OCR0A = 249;
	TIMSK0 = 0x02;

	// Podesavanje globalne dozvole prekida
	sei();
}

/*********************************/

/**
 * ISR - prekidna rutina tajmera 0 u modu CTC
 */
ISR(TIMER0_COMPA_vect)
{
	// Inkrementovanje broja ms koje su prosle od pokretanja aplikacije
	ms++;
}
