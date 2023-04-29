#include <xc.h>
#include <pic18f4321.h>
#include "T_PLAY_RECORD.h"
#include "T_JOYSTICK.h"
#include "T_SIO.h"
#include "T_RECORD_LIST.h"
#include "T_LCD.h"
#include "T_MELODY.h"
#include "T_KEYPAD.h"

static char state;
static char *recordList;
static char ADRPW;
static char numRecs;
static char noRecsMsg[] = {'N', 'O', ' ', 'R', 'E', 'C', 'O', 'R', 'D', 'S', '!', '!', '!', '\0'};
static char playMsg[] = {'P', 'L', 'A', 'Y', 'I', 'N', 'G', '.', '.', '.', '\0'};
static char first;
static char id[2];
static char ADR;
static char OP;
static char i;

void initPlayRecord(void){
    state = 0;
}

void motorPlayRecord(void) {
	switch(state) {
		case 0:

		break;
		case 1: 
			if (numRecs == 0) {
				LcPutString(noRecsMsg);
				state = 3;
			}
			else if (numRecs != 0 && getKey() == (char) -1) {
                LcClear();
				if(numRecs <= (char) 8) {
				    ADR = 0 + OP * 6;
				} else {
				    ADR = ADRPW * 6 + OP * 6;
					if(ADR > 47) {
						ADR = ADR - 48;
					}
				}
				i = 0;
                LcGotoXY(0,0);
				if(recordList[ADR] > '0') {
				    LcPutChar(recordList[ADR]);
				}
				ADR++;
				first = 1;
				state = 2;
			}
		break;
		case 2:
			if(i > 4) {
			    if(ADR >= 47) ADR = 0;
			    first = 0;
			    i = 0;
                    if((OP == 7 && numRecs > 7) ||  (OP == numRecs - 1 && numRecs <= 7)){
                    state = 5;
                    break;
                }
			    LcGotoXY(0,1);
			    if(recordList[ADR] > '0') {
			        LcPutChar(recordList[ADR]);
			        ADR++;
			    }
			}
			if(i == 1) {
			    LcPutChar(' ');
			    LcPutChar('-');
			    LcPutChar(' ');
			}
			if(i == 3) {
			    LcPutChar(':');
			}
			LcPutChar(recordList[ADR]);
			ADR++;
			i++;
			state = 4;
		break;
		case 3:
			if (stringIsFinished() == 1) {
				state = 0;
			}
		break;
		case 4:
			if (((i <= 5 && first == 1) || i <= 4)) {
				state = 2;
			}
			else if ((i > 4 && first == 0) || (i > 4 && OP >= numRecs) || (i  > 4 && OP >= 7 && numRecs >= 8)) {
				state = 5;
			}
		break;
		case 5:
			if ((getGoDown() == 1) && ((numRecs > 7 && OP < 7) || (numRecs <= 7 && OP < numRecs - 1))) {
                resetMoves();
				OP++;
				state = 6;
			}
			else if ((getGoUp() == 1) && OP > 0) {
                resetMoves();
				OP--;
				state = 6;
			} else if((~((getGoUp() == 1) && OP > 0)) && (~((getGoDown() == 1) && ((numRecs > 7 && OP < 7) || (numRecs <= 7 && OP < numRecs - 1)))) && (getKey() == '#')) {
                state = 7;
            }
		break;
		case 6:
			if (getKey() != '#') {
				state = 1;
			}
			else if (getKey() == '#') {
				state = 7;
			}
		break;
		case 7:
			if (SiIsAvailable()) {
				SiSendChar('P');
				LcClear();
				LcPutString(playMsg);
				state = 8;
			}
		break;
		case 8:
			if (stringIsFinished() == 1 && SiCharAvail() != (char) -1 && SiGetChar() == 'K') {
                if(numRecs <= 8) {
                    ADR = 0 + OP * 6;
                } else {
                    ADR = ADRPW * 6 + OP * 6;
                }
                if(ADR > 47) {
                    ADR = ADR - 48;
                }

                id[0] = recordList[ADR];
                id[1] = recordList[ADR + 1];
				state = 9;
			}
		break;
		case 9:
			if (SiIsAvailable()) {
				if(id[0] > 0) {
				    SiSendChar(id[0]);
				}
				state = 10;
			}
		break;
		case 10:
			if (SiIsAvailable()) {
				SiSendChar(id[1]);
				state = 11;
			}
		break;
		case 11:
			if (SiIsAvailable()) {
				SiSendChar('\0');
				state = 12;
			}
		break;
		case 12:
			if (SiCharAvail() != (char) -1 && SiGetChar() == 'F') {
				playMelody();
				state = 1;
			}
		break;
	}
}

void enablePlayRecord(void){
    recordList = getRecordList();
    ADRPW = getADRPW();
    numRecs = getNumRecs();
    resetMoves();
    LcClear();
    state = 1;
    OP = 0;
    id[0] = '0';
    id[1] = '0';
}

void disablePlayRecord(void){
     state = 0;
}
