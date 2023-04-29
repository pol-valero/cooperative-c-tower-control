#include <pic18f4321.h>
#include <xc.h>
#include "T_CURRENT_TIME.h"
#include "T_TIMER.h"
#include "T_SIO.h"
#include "T_JOYSTICK.h"
#include "T_MELODY.h"
#include "T_RECORD_LIST.h"

#include "T_LCD.h"  //TODO: DEBUG

#define MAX_TICS_REC 1

static char index[2]; //En ASCII!
static char *timestamp; //En ASCII!
static char i;
static char isFinished;
static char state;
static char byteReceived;
static unsigned char tmr_rec;


void initRecord(){
    TI_NewTimer(&tmr_rec);
    TRISAbits.TRISA1 = 1;
    state = 0;
}

void motorRecord(void) {
	switch(state) {
		case 0:

		break;
		case 1:
			if (SiIsAvailable()) {
				SiSendChar('D');
				TI_ResetTics(tmr_rec);
				index[0] = 0;
				index[1] = 0;
                disableJoystick();
				state = 2;
			}
		break;
		case 2:
			if (TI_GetTics(tmr_rec) >= MAX_TICS_REC) {
                TI_ResetTics(tmr_rec);
				ADCON0bits.GO = 1;
				state = 3;
			}
		break;
		case 3:
			if (/*ADCON0bits.GO == 0 &&*/  SiIsAvailable()) {
				SiSendChar(127);
				state = 4;
			}
		break;
		case 4:
			if (SiCharAvail() == (char) -1) {
				state = 2;
			}
			else if (SiCharAvail() != (char) -1) {
				index[0] = SiGetChar();
				timestamp = getTimestamp();
				state = 10;
			}
		break;
		case 5:
			if (SiCharAvail() != (char) -1) {
				byteReceived = SiGetChar();
				state = 6;
			}
        break;
		case 6:
			if (byteReceived == '\0') {
				i = 0;
				state = 7;
			}
			else if (byteReceived != '\0') {
				index[1] = SiGetChar();
				state = 9;
			}
		break;
		case 7:
			if (SiIsAvailable()) {
				SiSendChar(timestamp[i]);
				state = 8;
			}
		break;
		case 8:
			if (i >= 4) {
				isFinished = 1;
                playMelody();
				enableJoystick();
                saveRecord(timestamp, index);
				state = 0;
			}
			else if (i < 4) {
                i++;
				state = 7;
			}
		break;
		case 9:
			if (SiCharAvail() != (char) -1 && SiGetChar() == '\0') { 
				i = 0;
				state = 7;
			}
		break;
        case 10:
			if (SiIsAvailable() == 1) {
				SiSendChar('\0');
				state = 5;
			}
		break;
	}
}

void doRecord(){
    isFinished = 0;
    state = 1;
}

char recordFinished(){
    return isFinished;
}