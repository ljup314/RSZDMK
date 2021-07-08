
#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/**
 *  ISR - prekidna rutina taajmera 0 u modu CTC
 */
ISR(TIMER0_COMPA_vect);

/**
 * timer0InteruptInit - fja koja inicijalizuje timer0 tkd pravi prekide svake milisekunde
 * @return - nema povratnu vrednost
 */
void timer0InteruptInit();

/**
 * timer0millis - fja koja bezbedno vraca kao povratnu vrednost broj ms proteklih od spustanja naseg koda na plocu
 * @return - povratna vrednost je tipa uint32_t i ima vrednost broja ms proteklih od pocetka merenja vremena
 */
uint32_t timer0millis();

/**
 * timer0DelaysMs - fja koja implementira pauzu u broju ms koji je prosledjen kao parametar
 * @param delay_length - ulaz tipa uint32_t - duzina pauze u ms
 * @return - povratna vrednost je tipa unsigned long i ima vrednost broja ms proteklih od pocetka aplikavije do trenutka izlaska iz fje
 */
uint64_t timer0DelayMs(unsigned long delay_length);

#endif /* TIMER0_H_ */
