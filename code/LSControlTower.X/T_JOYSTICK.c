#include "T_JOYSTICK.h"

#include <xc.h>

static char changeAux;
static char go_up;
static char go_down;

void initJoystick(void) {
	//Init port
    TRISAbits.TRISA0 = 1;

    //Initialize variables
    go_down = 0;
    go_down = 0;
    
}

void motorJoystick(void) {
	static char state = 0;

	switch(state) {
		case 0:
			ADCON0bits.GO = 1;
			state = 1;
		break;
		case 1:
			if ((ADCON0bits.GO == 0) && (ADRESH > 217)) {
				go_up = 1;
				state = 2;
			}
			else if ((ADCON0bits.GO == 0) && (ADRESH < 38)) {
				go_down = 1;
				state = 3;
			}
			else if ((ADCON0bits.GO == 0) && ((ADRESH >= 38) || (ADRESH <= 217))) {
				state = 0;
			}
		break;
		case 2:
			ADCON0bits.GO = 1;
			state = 4;
		break;
		case 3:
			ADCON0bits.GO = 1;
			state = 4;
		break;
		case 4:
			if ((ADCON0bits.GO == 0) && (ADRESH > 116) && (ADRESH < 139) && (go_down = 0) && (go_up = 0)) {
				state = 0;
			}
			else if ((ADCON0bits.GO == 0) && ((ADRESH <= 116) || (ADRESH >= 139) || (go_down = 1) || (go_up = 1))) {
				ADCON0bits.GO = 1;
			}
		break;
	}
}

char getGoDown(void) {
    changeAux = go_down;
    go_down = 0;
    return changeAux;
}

char getGoUp(void) {
    changeAux = go_up;
    go_up = 0;
    return changeAux; 
}

void resetMoves(void){
    go_down = 0;
    go_up = 0;
}
