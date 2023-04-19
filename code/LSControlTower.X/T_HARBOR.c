#include <pic18f4321.h>
#include "T_HARBOR.h"
#include "Keypad.h"
#include "LcTLCD.h"
#include "TAD_TIMER.h"
#include "T_MENU.h"
#include "SIO.h"




#define END_CHAR '0'
#define ONE_SECOND 5000

const char* promptStr = "PORT NAME:0";
char harborName[4];

char i;
char j;
char currentKeyNum;

unsigned char tmr_handler;

void initHarbor() {
    TI_NewTimer(&tmr_handler);
    i = j = currentKeyNum = 0;
}


void motorHarbor(void) {
	
    static char state = 0;

	switch(state) {
		case 0:
			if (promptStr[i] != END_CHAR) {
				LcPutChar(promptStr[i]);
				i++;
			}
			else if (promptStr[i] == END_CHAR) {
				LcGotoXY(0,1);
				state = 1;
			}
		break;
		case 1:
			if (getKey() != (char) -1) {
				harborName[j] = getKey();
				currentKeyNum = getKeyNum();
				LcPutChar(harborName[j]);
				state = 2;
			}
		break;
		case 2:
			if (getKey() == (char) -1) {
				TI_ResetTics(tmr_handler);
				state = 3;
			}
			else if (getKey() == '*') {
				j=0;
				resetIndexSMS();
				state = 10;
			}
			else if (getKey() == '#' && j == 3) {
				state = 4;
			}
		break;
		case 3:
			if (getKey() != (char) -1 && TI_GetTics(tmr_handler)<ONE_SECOND && currentKeyNum == getKeyNum()) {
				harborName[j] = getKey();
				LcGotoXY(j,1);
				LcPutChar(harborName[j]);
				state = 2;
			}
			else if ((getKey() == (char) -1 && TI_GetTics(tmr_handler)>=ONE_SECOND) || (getKey() != (char) -1 && currentKeyNum != getKeyNum())) {
				j++;
				resetIndexSMS();
				state = 1;
			}
		break;
		case 10:
			if (getKey() == (char) -1) {
				LcClear();
				state = 0;
			}
		break;
		case 4:
			if (SiIsAvailable() == (char) 1) {
				SiSendChar('T');
				state = 5;
			}
		break;
		case 5:
			if (SiCharAvail() != (char) -1 && SiGetChar() == 'K') {
				j=0;
				state = 6;
			}
		break;
		case 6:
			if (SiIsAvailable() == (char) 1) {
				SiSendChar(harborName[j]);
				j++;
				state = 7;
			}
		break;
		case 7:
			if (harborName[j] != END_CHAR) {
				state = 6;
			}
			else if (harborName[j] == END_CHAR && SiIsAvailable() == (char) 1) {
				SiSendChar(harborName[j]);
				state = 8;
			}
		break;
		case 8:
			if (getKey() == (char) -1) {
				LcClear();
				//showMainMenu(); //TODO
				state = 9;
			}
		break;
		case 9:

		break;
	}
}