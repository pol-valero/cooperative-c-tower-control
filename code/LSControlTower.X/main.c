#include <xc.h>
#include <pic18f4321.h>

#include "T_TIMER.h"
#include "T_LCD.h"
#include "T_KEYPAD.h"
#include "T_SIO.h"
#include "T_HARBOR.h"
#include "T_MENU.h"
#include "T_JOYSTICK.h"

#pragma config OSC = HSPLL
#pragma config PBADEN = DIG
#pragma config WDT = OFF
#pragma MCLRE = ON

// HGIH_RSI pel timer.
void __interrupt(high_priority) High_RSI(void) {
    RSI_Timer0();
}

void main(void) {
    /************************
     * INIT IRQS
     ***********************/
    RCONbits.IPEN = 0;  
    INTCONbits.GIE = 1; 
    INTCONbits.PEIE = 1;        
    
    /************************
     * INIT TMR & SIO
     ***********************/
    TI_Init ();
    initSIO();
    
    /************************
     * INIT ADC
     ***********************/    
    ADCON1 = 0x0D; //00001101
    ADCON2 = 0x03; //00000011
    ADCON0 = 0x01; //00000001
        
    /************************
     * INIT TADs
     ***********************/
    initHarbor();
    initKeypad();
    
    /************************
     * MOTORS LOOP
     ***********************/
    while(1) {
        motorKeypad();
        motorHarbor();
        
    }
    
    return;
}
