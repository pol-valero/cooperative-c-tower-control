#include <pic18f4321.h>
#include <xc.h>
#include "T_JOYSTICK.h"

static char changeAux;
static char go_up;
static char go_down;
static char state;

void initJoystick(void) {
	//Init port
    TRISAbits.TRISA0 = 1;
    // Selects CH0
    ADCON0bits.CHS0 = 0;
    //Initialize variables
    go_down = 0;
    go_up = 0;
    state = 0;
}

void motorJoystick(void) {
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
			else if ((ADCON0bits.GO == 0) && ((ADRESH >= 38) && (ADRESH <= 217))) {
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
			if ((ADCON0bits.GO == 0) && (ADRESH > 116) && (ADRESH < 139)) {
				state = 0;
                go_down = 0;
                go_up = 0;
                
			}
			else if ((ADCON0bits.GO == 0) && ((ADRESH <= 116) || (ADRESH >= 139))) {
				ADCON0bits.GO = 1;
			}
		break;
        case 5:

		break;
	}
}

char getGoDown(void) {
    return go_down;
}

char getGoUp(void) {
    return go_up;
}

void resetMoves(void){  
    go_down = 0;
    go_up = 0;
}

void disableJoystick() { 
    go_down = 0;
    go_up = 0;
    state = 5;
    // Selects CH1
    ADCON0bits.CHS0 = 1;
}

void enableJoystick() {  
    go_down = 0;
    go_up = 0;
    state = 0;
    // Selects CH0
    ADCON0bits.CHS0 = 0;
}
