#include <xc.h>
#include <pic18f4321.h>
#include "T_MENU.h"
#include "T_CURRENT_TIME.h"
#include "T_JOYSTICK.h"
#include "T_LCD.h"
#include "T_KEYPAD.h"
#include "T_MARQUEE.h"
#include "T_PLAY_RECORD.h"
#include "T_RECORD.h"
#include "T_TIMER.h"

#define MAX_TICS_END 8000

static char the_end;
static char* towerName;
unsigned static char tmr_end;
static char OP;
static char endMsg[] = {'b', 'y', 'e', ' ', 'b', 'y', 'e', ' ', '\0'};
static char recordMsg[] = {'R', 'E', 'C', 'O', 'R', 'D', 'I', 'N', 'G', '.', '.', '.', '\0'};
static char state;


void initMenu(void) {
    TI_NewTimer(&tmr_end);
    //Init vars
    OP = 0;
    state = 0;
    the_end = 0;
}

void motorMenu(void) {
	switch(state) {
		case 0:

		break;
		case 1:
            hideCurrentTime();
			activateMarquee(OP);  
			state = 2;
		break;
		case 2:
			if (((~((getGoUp() == 1) && (OP > 0))) && (~((getGoDown() == 1) && (OP < 4)))) && (getKey() == '#')) {
				disableMarquee(); 
				state = 3;
			}
			else if ((getGoDown() == 1) && (OP < 4)) {   
				OP++;
                resetMoves();
				state = 1;
			}
			else if ((getGoUp() == 1) && (OP > 0)) {
				OP--;
                resetMoves();
				state = 1;
			}
		break;
		case 3:
			if (OP == 0) {
                doRecord();
                LcClear();
                LcGotoXY(0,0);
                LcCursorOff();
                LcPutString(recordMsg);
				state = 4;
			}
			else if (OP == 1) {
				state = 5;
			}
			else if (OP == 3) {
                showCurrentTime();
				state = 6;
			}
			else if (OP == 2) {
				showModifyTime();
				state = 7;
			}
			else if (OP == 4) {  
                LcClear();
                LcPutString(endMsg);  
				state = 8;
			}
		break;
		case 6:
            if(getKey() == (char) -1) {
                state = 11;
            }
		break;
		case 5:

		break;
		case 4:
            if ((stringIsFinished() == 1) && (recordFinished() == 1)) {
                state = 1;
            }
		break;
		case 7:
			if (getFinishedModify() == 1) {
				state = 13;
			}
			else if (getKey() == '*') {
				hideModifyTime();
				state = 14;
			}
		break;
		case 8:
            if (stringIsFinished() == 1) { 
				LcPutString(towerName);   
				state = 9;
			}
		break;
		case 9:
			if (stringIsFinished() == 1) {
                LcPutChar('!');
                TI_ResetTics(tmr_end);
				state = 10;
                
			}
		break;
        
        case 10:
            if (TI_GetTics(tmr_end) >= MAX_TICS_END) {
				the_end = 1;
				state = 0;         
			} 
        break;
        
        case 11:
            if(getKey() == '*') {
                hideCurrentTime();
                state = 12;
            } 
        break;
        case 12:
            if(getKey() == (char) -1) {
                state = 1;
            }
        break;
        case 13:
			if (getKey() == '#') {
				setSaveTime();
				state = 14;
			}
			else if (getKey() == '*') {
				hideModifyTime();
				state = 14;
			}
		break;
		case 14:
			if (getKey() == (char) -1) {
				state = 1;
			}
		break;
	}
}

void showMainMenu(void){
    OP = 0;
    state = 1;
    the_end = 0;
    resetMoves();
    startTime();
}

void setTowerName(char* tower){
    towerName = tower;
}

char getTheEnd(void){
    return the_end;
}
