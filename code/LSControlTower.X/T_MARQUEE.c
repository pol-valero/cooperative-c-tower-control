#include <xc.h>
#include <pic18f4321.h>
#include "T_MARQUEE.h"
#include "T_LCD.h"
#include "T_TIMER.h"

#define MAX_TICS_MARQUEE 5000

const char* menuOp[] = {
    "1.START RECORDING     \0",
    "2.PLAY RECORDINGS     \0",
    "3.MODIFY CURRENT TIME \0",
    "4.SHOW CURRENT TIME   \0",
    "5.END COMMUNICATION   \0",
    "                      \0"
};

const char OpLen[] = {
    18,22,22,20,20
};

static char shift;
static char i;
static unsigned char tmr_marquee;
static char state;
static char OP;

void initMarquee(void){
    TI_NewTimer(&tmr_marquee);
    i = 0;
    shift = 0;
    state = 0;
}

void motorMarquee(void) {
	switch(state) {
		case 0:

		break;
		case 1:
            if (shift + i >= OpLen[OP]) {
                  LcPutChar(menuOp[OP][i + shift - OpLen[OP]]);
            } else {
                LcPutChar(menuOp[OP][i + shift]);
            }

            i++;
			state = 2;
		break;
		case 2:
			if (i >= 16) {
                LcGotoXY(0,1);
				i = 0;
				state = 3;
			}
			else if (i < 16) {
				state = 1;
			}
		break;
		case 3:
			if (i >= 16) {
				i = 0;
				TI_ResetTics(tmr_marquee);
				state = 4;
			}
			else if (i < 16) {
                if (shift + i >= OpLen[OP]) {
                      LcPutChar(menuOp[OP + 1][i + shift - OpLen[OP]]);
                } else {
                    LcPutChar(menuOp[OP + 1][i + shift]);
                }
                i++;
			}
		break;
		case 4:
			if (TI_GetTics(tmr_marquee) >= MAX_TICS_MARQUEE) {
				shift++;
                LcGotoXY(0,0);
                if(shift >= OpLen[OP]) {
                    shift = 0;
                }
				state = 1;
			}
		break;
	}
}

void activateMarquee(char op){
    LcGotoXY(0,0);
    i = 0;
    //shiftUp = 0;
    //shiftDown = 0;
    shift = 0;
    state = 1;
    OP = op;
}

void disableMarquee(){
    state = 0;
}
