#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "pls7.h"
#include "timer0.h"
#include "timer0.c"

typedef enum state_t  {F1O, F1C, F2O, F2C, F3O, F3C, F4O, F4C, FM} state_t; //preimenovali smo enum state_t da se zove samo state_t (tip podatka)

void openDoor(uint8_t sprat)
{
	writeDisplay(sprat, 0xe4);
}

void closedDoor(uint8_t sprat)
{
	writeDisplay(sprat, 0xe5);
}

void brisi()
{
	writeDisplay(D1, 0xff);
	writeDisplay(D2, 0xff);
	writeDisplay(D3, 0xff);
	writeDisplay(D4, 0xff);
}

uint8_t ocitajTaster()
{
	if(buttonState(LEFT))
		return 1;
	else if(buttonState(DOWN))
		return 2;
	else if(buttonState(RIGHT))
		return 3;
	else if(buttonState(UP))
		return 4;
}

uint8_t switchLow()
{
if(switchState(S1) == 0 && switchState(S2) == 0) //prvi sprat
	return 4;
else if(switchState(S1) == 0 && switchState(S2) == 1) //drugi sprat
	return 3;
else if(switchState(S1) == 1 && switchState(S2) == 0) //treci sprat
	return 2;
else if(switchState(S1) == 1 && switchState(S2) == 1) //cetvrti sprat
	return 1;
}

void ledsOn()
{
	writeDisplay(LEDS, 0x00);
}

void ledsOff()
{
	writeDisplay(LEDS, 0x55);
}

int16_t main()
{
	timer0InteruptInit(); //inicijalizujemo tajmer  biblioteku
	init();
	
	int8_t current_floor, target_floor = 0;
	writeDisplay(LEDS, 0x00); //na pocetku su sve diode ukljucene
	state_t state = F1O; 
	uint8_t taster;
	
	while(1)
	{
		switch(state)
		{
			case F1O:
				openDoor(D1); //u ovoj fji ocekuje se da unesemo odgovarajuci displej 7seg displeja
				current_floor = 0;
				taster = ocitajTaster();
				if(taster == 1)
				{
					brisi();
					closedDoor(1);
					ledsOn();
					state = F1C;
				}
				else
					state = F1O;
			break;
			case F1C:
				taster = ocitajTaster();
				if(taster == 3) //ako pritisnemo desni taster
				{
					if(~switchLow() == 1) //oba prekidaca neaktivna, prvi sprat 
					{
						ledsOn();
						brisi();
						openDoor(1);
						state = F1O;
					}
					else
					{
						target_floor = switchLow();
						state = FM;
					}
				}
				else
					state = F1C;
			break;
			case F2O:
				taster = ocitajTaster();
				if(taster == 1)
				{
					ledsOff();
					brisi();
					closedDoor(2);
					state = F2C;
				}
				else
					state = F2O;
			break;
			case F2C:
				taster = ocitajTaster();
				if(taster == 3) //ako je pritisnut desni taster
				{
					if(~switchLow() == 2)
					{
						ledsOn();
						brisi();
						openDoor(2);
						state = F2O;
					}
					else
					{
						target_floor = switchLow();
						state = FM;
					}
				}
				else
					state = F2C;
			break;
			case F3O:
				taster = ocitajTaster();
				if(taster == 1)
				{
					ledsOff();
					brisi();
					closedDoor(3);
					state = F3C;
				}
				else
					state = F3O;
			break;
			case F3C:
				taster = ocitajTaster();
				if(taster == 3) //ako je pritisnut desni taster
				{
					if(~switchLow() == 3)
					{
						ledsOn();
						brisi();
						openDoor(3);
						state = F3O;
					}
					else
					{
						target_floor = switchLow();
						state = FM;
					}
				}
				else
					state = F3C;
			break;
			case F4O:
				taster = ocitajTaster();
				if(taster == 1)
				{
					ledsOff();
					brisi();
					closedDoor(4);
					state = F4C;
				}
				else
					state = F4O;
			break;
			case F4C:
				taster = ocitajTaster();
				if(taster == 3) //ako je pritisnut desni taster
				{
					if(~switchLow() == 4)
					{
						ledsOn();
						brisi();
						openDoor(4);
						state = F4O;
					}
					else
					{
						target_floor = switchLow();
						state = FM;
					}
				}
				else
					state = F4C;
			break;
			case FM:
				if(current_floor == target_floor)
				{
					if(target_floor == 1)
						state = F1O;
					else if(target_floor == 2)
						state = F2O;
					else if(target_floor == 3)
						state = F3O;
					else if(target_floor == 4)
						state = F4O;
					ledsOn();
					openDoor(switchLow());
				}
				else if(current_floor < target_floor)
				{
					current_floor++;
					timer0DelayMs(1000);
				}
				else
				{
					current_floor--;
					timer0DelayMs(1000);
				}
			break;
		}
	}
	return 0;
}