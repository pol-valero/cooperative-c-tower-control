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

#define MAX_TICS_END 10000

static char the_end;
static char* towerName;
unsigned static char tmr_end;
static char OP;
const char endMsg[] = {'b', 'y', 'e', ' ', 'b', 'y', 'e', ' ', '\0'};
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
			activateMarquee(OP);  
            resetMoves();
			state = 2;
		break;
		case 2:
			if (((~((getGoUp() == 1) && (OP > 0))) && (~((getGoDown() == 1) && (OP < 4)))) && (getKey() == '#')) {
				disableMarquee(); 
				state = 3;
			}
			else if ((getGoDown() == 1) && (OP < 4)) {
				OP++;
				state = 1;
			}
			else if ((getGoUp() == 1) && (OP > 0)) {
				OP--;
				state = 1;
			}
		break;
		case 3:
			if (OP == 0) {
				state = 4;
			}
			else if (OP == 1) {
				state = 5;
			}
			else if (OP == 2) {
				state = 6;
			}
			else if (OP == 3) {
				state = 7;
			}
			else if (OP == 4) {
				//LcPutString(endMsg);  //TODO: POSARE
				state = 8;
			}
		break;
		case 6:

		break;
		case 5:

		break;
		case 4:

		break;
		case 7:

		break;
		case 8:
            if (/*printFinished() ==*/ 1) { //TODO: POSARE
				//LcPutString(portName);    //TODO: POSARE
				TI_ResetTics(tmr_end);
				state = 9;
			}
		break;
		case 9:
			if (TI_GetTics(tmr_end) >= MAX_TICS_END) {
				the_end = 1;
				state = 0;
			}
		break;
	}
}

void showMainMenu(void){
    OP = 0;
    state = 1;
    the_end = 0;
}

void setTowerName(char* tower){
    towerName = tower;
}

char getTheEnd(void){
    return the_end;
}
