#include <xc.h>
#include <pic18f4321.h>

#include "T_CURRENT_TIME.h"
#include "T_HARBOR.h"
#include "T_JOYSTICK.h"
#include "T_KEYPAD.h"
#include "T_LCD.h"
#include "T_MARQUEE.h"
#include "T_MELODY.h"
#include "T_MENU.h"
#include "T_PLAY_RECORD.h"
#include "T_QUEUE.h"
#include "T_RECORD.h"
#include "T_RECORD_LIST.h"
#include "T_SIO.h"
#include "T_TIMER.h"

#pragma config OSC = HSPLL
#pragma config PBADEN = DIG
#pragma config WDT = OFF
#pragma MCLRE = ON

#pragma config DEBUG = OFF  //TODO: Test
#pragma config PWRT = OFF   //TODO: Test
#pragma config BOR = OFF   //TODO: Test
#pragma config WDT = OFF   //TODO: Test
#pragma config LVP = OFF   //TODO: Test

// HGIH_RSI pel timer.
void __interrupt(high_priority) High_RSI(void) {
    RSI_Timer0();
}

void main(void) {
    /************************
     * INIT IRQS
     ***********************/
    RCONbits.IPEN = 1;      //TODO: Test
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
    ADCON2 = 0x12; //00000011   //TODO: Test
    ADCON0 = 0x01; //00000001
        
    /************************
     * INIT TADs
     ***********************/
    initHarbor();
    initKeypad();
    initMenu();
    initMarquee();
    initJoystick();
    
    /************************
     * MOTORS LOOP
     ***********************/
    while(1) {
        motorKeypad();
        motorHarbor();
        motorMenu();
        motorMarquee();
        motorJoystick();
    }
    
    return;
}
