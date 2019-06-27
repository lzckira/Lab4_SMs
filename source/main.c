/*	Author: zlian030
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #1
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

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; // Configure port B's 7 pins as inputs
    DDRB = 0xFF; PORTB = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s
    enum States {start, LED1On, LED1Release, LED2On, LED2Release} state;
//    unsigned short tmpA = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}


void Tick() {
    switch(state) {
	case start:
	    state = LED1On;
	    break;
	case LED1On:
	    state = (PINA & 0x01) ? LED1Release : LED1On;
	    break;
        case LED1Release:
            state = !(PINA & 0x01) ? LED2On : LED1Release;
            break;
	case LED2On:
	    state = (PINA & 0x01) ? LED2Release : LED2On;
	    break;
        case LED2Release:
            state = !(PINA & 0x01) ? LED1On : LED2Release;
            break;
	default:
	    state = LED1On;
	    break;

    switch(state) {
        case start:
            PORTB = 0x01;
            break;
        case LED1On:
            PORTB = 0x01;
            break;
        case LED1Release:
	    PORTB = 0x02;
            break;
        case LED2On:
	    PORTB = 0x02;
            break;
        case LED2Release:
	    PORTB = 0x01;
            break;
        default:
	    PORTB = 0x01;
            break;
    }
    
    
    
}
