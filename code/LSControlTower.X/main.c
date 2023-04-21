#include <xc.h>
#include <pic18f4321.h>

#include "T_TIMER.h"
#include "T_LCD.h"
#include "T_KEYPAD.h"
#include "T_SIO.h"
#include "T_HARBOR.h"
#include "T_MENU.h"
#include "T_JOYSTICK.h"

#pragma config OSC = INTIO2
#pragma config PBADEN = DIG
#pragma config WDT = OFF
#pragma MCLRE = ON

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
     * INIT TMR & SIO
     ***********************/
    TI_Init ();
    initSIO();
    initHarbor();
    
    /************************
     * INIT TADs
     ***********************/
    
    /************************
     * MOTORS LOOP
     ***********************/
    while(1) {
        motorKeypad();
        motorHarbor();
        
        motorJoystick();
    }
    
    return;
}
