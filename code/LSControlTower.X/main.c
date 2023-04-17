#include <pic18f4321.h>
#include <xc.h>

#include "TAD_TIMER.h"
#include "LcTLCD.h"

#pragma config OSC = INTIO2
#pragma config PBADEN = DIG
#pragma config WDT = OFF


void main(void) {
    /************************
     * INIT OSC (16MHz)
     ***********************/
    
    OSCCON = 0b01100000;
    OSCTUNEbits.PLLEN = 1;
    return;
}
