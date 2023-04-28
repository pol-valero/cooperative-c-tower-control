#include <xc.h>
#include <pic18f4321.h>
#include "T_HARBOR.h"
#include "T_KEYPAD.h"
#include "T_LCD.h"
#include "T_TIMER.h"
#include "T_MENU.h"
#include "T_SIO.h"




#define END_CHAR 0
#define ONE_SECOND 4000

static const char* promptStr = "PORT NAME:\0";
static char harborName[4];

static char i;
static char j;
static char currentKeyNum;

static unsigned char tmr_handler;

void initHarbor() {
    TI_NewTimer(&tmr_handler);
    i = j = currentKeyNum = 0;
    harborName[3] = '\0';
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
                LcCursorOn();
				state = 1;
			}
		break;
		case 1:
			if ((getKey() != (char) -1 && j < 3) || (getKey() == '#' ) || getKey() == '*') {
                if (getKey() != '#' && getKey() != '*') {
                    currentKeyNum = getKeyNum();
                    harborName[j] = getKey();
                    LcPutChar(harborName[j]);
                    if (j == 2) {
                        LcCursorOff();
                    }
                }
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
			else if (getKey() == '#' && j >= 2) {
				state = 4;
			}
		break;
		case 3:
			if (getKey() != (char) -1 && getKey() != '#' && TI_GetTics(tmr_handler)<ONE_SECOND && currentKeyNum == getKeyNum()) {
				harborName[j] = getKey();
				LcGotoXY(j,1);
				LcPutChar(harborName[j]);
				state = 2;
			}
			else if ((getKey() == (char) -1 && TI_GetTics(tmr_handler)>=ONE_SECOND) || (getKey() != (char) -1 && currentKeyNum != getKeyNum())) {
				if (getKey() != '#') {
                    j++;
                }
				resetIndexSMS();
				state = 1;
			}
            
		break;
		case 10:
			if (getKey() == (char) -1) {
				LcClear();
				state = 0;
                i = 0;
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
				showMainMenu();
                setTowerName(harborName);
				state = 9;
			}
		break;
		case 9:
            if(getTheEnd() == 1) {
                state = 0;
                currentKeyNum = 0;
                j = 0;
                i = 0;
                LcClear();
            }
		break;
	}
}