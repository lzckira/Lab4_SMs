/*	Author: zlian030
 *  Partner(s) Name: 
 *	Lab Section: 021
 *	Assignment: Lab #4  Exercise #2
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

enum States {start, pressPound, releasePound, pressY, unlock, lock, resetUnlock, resetLock} state;
unsigned char flag = 0x00;
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
	    state = resetLock;
	    break;
	case pressPound:
	    if ((PINA & 0x04) && !(PINA & 0x03)) {
		state = releasePound;
	    }
	    else {
		state = (flag) ? resetLock :resetUnlock;
	    }
            break;
	case releasePound:
	    if (!(PINA & 0x07)) {
		state = pressY;
	    }
	    else if ((PINA & 0x04) && !(PINA & 0x03)) {
		state = releasePound;
	    }
	    else {
		state = (flag) ? resetLock : resetUnlock;
	    }
            break;
	case pressY:
            if ((PINA & 0x02) && !(PINA & 0x05)) {
                state = (flag) ? lock : unlock;
            }
            else if (!(PINA & 0x07)) {
                state = pressY;
            }
            else {
		state = (flag) ? resetUnlock : resetLock;
            }
            break;
	case unlock:
	    state = resetUnlock;
            break;
	case lock:
	    state = resetLock;
	    break;
	case resetUnlock:
	    state = ((PINA & 0x04) && !(PINA & 0x03)) ? pressPound : resetUnlock;
	    if (PINA & 0x80) {
		state = lock;
	    }
            break;
        case resetLock:
            state = ((PINA & 0x04) && !(PINA & 0x03)) ? pressPound : resetLock;
            break;
	defalut:
            break;
    }

    switch(state) {
        case start: 
            PORTB = 0x00;
            break;
        case pressPound:
            break;
        case releasePound:
            break;
        case pressY:
            break;
        case unlock:
	    flag = 0x01;
	    PORTB = 0x01;
            break;
	case lock:
	    flag = 0x00;
	    PORTB = 0x00;
	    break;
	case resetUnlock:
	    PORTB = 0x01;
	    break;
        case resetLock:
	    PORTB = 0x00;
            break;
      //  defalut:
	   // PORTB = 0x00;
         //   break;
    } 

//    PORTC = state;    
}

