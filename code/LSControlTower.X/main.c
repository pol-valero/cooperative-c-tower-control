#include <pic18f4321.h>
#include <xc.h>

#include "TAD_TIMER.h"
#include "LcTLCD.h"
#include "Keypad.h"

#pragma config OSC = INTIO2
#pragma config PBADEN = DIG
#pragma config WDT = OFF

// HGIH_RSI pel timer.
void __interrupt(high_priority) High_RSI(void) {
    RSI_Timer0();
}

void main(void) {
    /************************
     * INIT OSC (16MHz)
     ***********************/
    OSCCON = 0b01100000;
    OSCTUNEbits.PLLEN = 1;
    
    /************************
     * INIT IRQS
     ***********************/
    RCONbits.IPEN = 0;          
    INTCONbits.PEIE = 1;        // Activa les interrupcions de baixa prioritat
    INTCONbits.GIE = 1; 
    
    /************************
     * INIT TMR
     ***********************/
    TI_Init ();
    
    /************************
     * INIT TADs
     ***********************/
    
    /************************
     * MOTORS LOOP
     ***********************/
    while(1) {
        motorKeypad();

    }
    
    return;
}
