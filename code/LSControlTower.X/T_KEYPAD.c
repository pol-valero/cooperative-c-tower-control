#include <xc.h>
#include <pic18f4321.h>
#include "T_KEYPAD.h"
#include "T_LCD.h"
#include "T_TIMER.h"
#include "T_MELODY.h"

#define MAX_TICS_BOUNCE  100

const char sms[4][3][5] = {
    {"1----", "ABC2-", "DEF3-"},
    {"GHI4-", "JKL5-", "MNO6-"},
    {"PQRS7", "TUV8-", "WXYZ9"},
    {"*----", "0 ---", "#----" }
};

const char keyNumber[4][3] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12}
};

unsigned char tmr_bounce; 
char key;
char keyNum;
char indexSMS;

void initKeypad() {
    // Init ports
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 0;

    // State 0 conditions
    LATCbits.LATC0 = 0;
    LATCbits.LATC1 = 1;
    LATCbits.LATC2 = 1;
    // Create the bounce timer
    TI_NewTimer(&tmr_bounce);
    // Initialize variables
    key = (char) -1;
    keyNum = (char) -1;
    indexSMS = 0;
}

void motorKeypad(void) {
	static char state = 0;
    static char colPressed;
    static char rowPressed;
    static char keyAux;
    
	switch(state) {
		case 0:
			if ((PORTB & 0x0F) == 0x0F) {
				LATCbits.LATC0 = 1;
				LATCbits.LATC1 = 0;
				LATCbits.LATC2 = 1;
				LATCbits.LATC3 = 1;
				state = 1;
			}
			else if ((PORTB & 0x0F) != 0x0F) {
				TI_ResetTics(tmr_bounce);
				state = 4;
			}
		break;
		case 1:
			if ((PORTB & 0x0F) == 0x0F) {
				LATCbits.LATC0 = 1;
				LATCbits.LATC1 = 1;
				LATCbits.LATC2 = 0;
				LATCbits.LATC3 = 1;
				state = 2;
			}
			else if ((PORTB & 0x0F) != 0x0F) {
				TI_ResetTics(tmr_bounce);
				state = 4;
			}
		break;
		case 2:
			if ((PORTB & 0x0F) == 0x0F) {
				LATCbits.LATC0 = 0;
				LATCbits.LATC1 = 1;
				LATCbits.LATC2 = 1;
				LATCbits.LATC3 = 1;
				state = 0;
			}
			else if ((PORTB & 0x0F) != 0x0F) {
				TI_ResetTics(tmr_bounce);
				state = 4;
			}
			else if ((PORTB & 0x0F) == 0x0F) {
				LATCbits.LATC0 = 1;
				LATCbits.LATC1 = 1;
				LATCbits.LATC2 = 1;
				LATCbits.LATC3 = 0;
				state = 3;
			}
		break;
		case 4:
			if ((TI_GetTics(tmr_bounce) >= MAX_TICS_BOUNCE) && ((PORTB & 0x0F) != 0x0F) ) {
				colPressed = ((~(PORTB & 0X07)) >> 1) & 0x7F;
				rowPressed = ((~(PORTC & 0x0F)) >> 1) & 0x7F;
				rowPressed = rowPressed == 3 ? 2 : rowPressed;
				rowPressed = rowPressed > 3 ? 3 : rowPressed;
				keyNum = keyNumber[rowPressed][colPressed];
				playNote(keyNum);
				keyAux = sms[rowPressed][colPressed][indexSMS++];
				if(keyAux == '-') {
				    indexSMS = 0;
				    key = sms[rowPressed][colPressed][indexSMS++];
				} else {
				    key = keyAux;
				}
				state = 5;
			}
			else if ((PORTB & 0x0F) == 0x0F) {
				LATCbits.LATC0 = 0;
				LATCbits.LATC1 = 1;
				LATCbits.LATC2 = 1;
				LATCbits.LATC3 = 1;
				state = 0;
			}
		break;
		case 5:
			if ((PORTB & 0x0F) == 0x0F) {
				TI_ResetTics(tmr_bounce);
				state = 6;
			}
		break;
		case 6:
			if ((TI_GetTics(tmr_bounce) >= MAX_TICS_BOUNCE) && ((PORTB & 0x0F) == 0x0F) ) {
				LATCbits.LATC0 = 0;
				LATCbits.LATC1 = 1;
				LATCbits.LATC2 = 1;
				keyNum = -1;
				key = -1;
				state = 0;
			}
			else if ((PORTB & 0x0F) != 0x0F) {
				state = 5;
			}
		break;
		case 3:
			if ((PORTB & 0x0F) != 0x0F) {
				TI_ResetTics(tmr_bounce);
				state = 4;
			}
		break;
	}
}

char getKey(void) {
    return key;
}

char getKeyNum(void) {
    return keyNum;
}

void resetIndexSMS(void) {
    indexSMS = 0;
}


