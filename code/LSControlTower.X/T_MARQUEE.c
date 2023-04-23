#include <xc.h>
#include <pic18f4321.h>
#include "T_MARQUEE.h"
#include "T_LCD.h"
#include "T_TIMER.h"

#define MAX_TICS_MARQUEE 5000

const char* menuOp[] = {
    "1.START RECORDING \0",
    "2.PLAY RECORDINGS \0",
    "3.MODIFY CURRENT TIME \0",
    "4.SHOW CURRENT TIME \0",
    "5.END COMMUNICATION \0"
    "                \0"
};

const char OpLen[] = {
    19,18,22,20,20
};

static char shiftUp;
static char shiftDown;
static char i;
static unsigned char tmr_marquee;
static char state;
static char OP;

void initMarquee(void){
    TI_NewTimer(&tmr_marquee);
    i = 0;
    shiftUp = 0;
    shiftDown = 0;
    state = 0;
}

void motorMarquee(void) {
	switch(state) {
		case 0:

		break;
		case 1:
			if(shiftUp >= OpLen[OP]) {
			    shiftUp = 0;
			    LcPutChar(menuOp[OP][i + shiftUp]);
			} else if (shiftUp + i >= OpLen[OP]) {
				  LcPutChar(menuOp[OP][i + shiftUp - OpLen[OP]]);
			} else {
			    LcPutChar(menuOp[OP][i + shiftUp]);
			}
			i++;
			state = 2;
		break;
		case 2:
			if (i >= 16) {
				LcGotoXY(0,1);
				if(i >= 16) i = 0;
				if(shiftDown >= OpLen[OP]) {
				    shiftDown = 0;
				    LcPutChar(menuOp[OP][i + shiftDown]);
				} else if (shiftDown + i >= OpLen[OP]) {
					  LcPutChar(menuOp[OP][i + shiftDown - OpLen[OP]]);
				} else {
				    LcPutChar(menuOp[OP][i + shiftDown]);
				}
				i++;
				state = 3;
			}
			else if (i < 16 ) {
				state = 1;
			}
		break;
		case 3:
			if (i >= 16) {
				i=0;
				TI_ResetTics(tmr_marquee);
				state = 4;
			}
			else if (i < 16 ) {
				state = 2;
			}
		break;
		case 4:
			if (TI_GetTics(tmr_marquee) >= MAX_TICS_MARQUEE) {
				shiftUp++;
				shiftDown++;
				state = 5;
			}
		break;
		case 5:

		break;
	}
}

void activateMarquee(char OP){
    i = 0;
    shiftUp = 0;
    shiftDown = 0;
    state = 1;
    
}

void disableMarquee(){
    state = 0;
}
