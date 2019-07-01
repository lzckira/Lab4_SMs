/*	Author: zlian030
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
//#include "RIMS.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, press, release, unlock, lock} state;
unsigned char flag = 0x00;
unsigned char password[] = {4, 1, 2, 1};
unsigned char cont = 0x00;
void Tick();

int main(void) {
/* Insert DDR and PORT initializations */
DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
//DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s


//    enum States {start, LED1On, LED1Release, LED2On, LED2Release} state;
//    unsigned short tmpA = 0x00;
    /* Insert your solution below */
    state = start;
    while (1) {
	Tick();
    }
    return 1;
}


void Tick() {
    switch(state) {
	case start:
	    state = press;
	    break;
	case press:
	    if (PINA == password[cont]) {
		state = release;
	    }
	    else if (PINA == 0x00) {
		state = press;
	    }
	    else {
		state = press;
		cont = 0x00;
                if ((PINA & 0x80) && (flag == 0x01)) {
                    state = lock;
                }
	    }
            break;
	case release:
	    if (PINA == 0x00) {
		state = press;
		cont = cont + 0x01;
	    }
	    else if (PINA == password[cont]) {
		state = release;
		if (cont == 0x03) {
		    cont = 0x00;
		    state = (flag) ? lock : unlock;
		}
	    }
	    else {
		state = (flag) ? unlock : lock;
		cont = 0x00;
		if ((PINA & 0x80) && (flag == 0x01)) {
		    state = lock;
		}
	    }
            break;
	case unlock:
	    state = (flag) ? press : unlock;
            break;
	case lock:
	    state = (flag) ? lock : press;
	    break;
//	defalut:
  //          break;
    }

    switch(state) {
        case start: 
            PORTB = 0x00;
            break;
        case press:
            break;
        case release:
            break;
        case unlock:
	    flag = 0x01;
	    PORTB = 0x01;
            break;
	case lock:
	    flag = 0x00;
	    PORTB = 0x00;
	    break;
      //  defalut:
	   // PORTB = 0x00;
         //   break;
    } 

//    PORTC = state;     
}

