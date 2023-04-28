#include <xc.h>
#include <pic18f4321.h>
#include "T_LCD.h"
#include "T_TIMER.h"
#include "T_KEYPAD.h"

#define MAX_TICS_SEG	4000

static char min[2];
static char seg[2];
static char timestamp[4];
static char showTime;
static unsigned char tmr_time; 
static char state;
static char state_mod;
static char saveNewTime;
static char finishedModify;
static char i;
static char newTime[4];

static char showMsg[] = {'C', 'U', 'R', 'R', 'E', 'N', 'T', ' ', 'T', 'I', 'M', 'E', ':', '\0'};
static char modifyMsg[] = {'M', 'O', 'D', 'I', 'F', 'Y', ' ', 'T', 'I', 'M', 'E', ':', '\0'};

void initCurrentTime(){
    TI_NewTimer(&tmr_time);
    showTime = 0;
    state_mod = 0;
}

void motorCurrentTime() {
	switch(state) {
		case 0:

		break;
		case 1:
			TI_ResetTics(tmr_time);
			state = 2;
		break;
		case 2:
			if (TI_GetTics(tmr_time) >= MAX_TICS_SEG ) {
				seg[0]++;
				state = 3;
			}
		break;
		case 3:
			if (seg[0] >= 10) {
				seg[0]=0;
				seg[1]++;
				state = 4;
			}
			else if (seg[0] < 10) {
				state = 7;
			}
		break;
		case 4:
			if (seg[1]  >= 6) {
				seg[1]=0;
				min[0]++;
				state = 5;
			}
			else if (seg[1]  < 6) {
				state = 7;
			}
		break;
		case 5:
			if (min[0] >= 10) {
				min[0]=0;
				min[1]++;
				state = 6;
			}
			else if (min[0] < 10) {
				state = 7;
			}
		break;
		case 6:
			if (min[1] >= 10) {
				min[1]=0;
				state = 7;
			}
			else if (min[1] < 10) {
				state = 7;
			}
		break;
		case 7:
			if (showTime == 1) {
                LcClear();
				LcGotoXY(0,0);
				LcPutString(showMsg);
				state = 8;
			}
			else if (showTime == 0) {
				state = 1;
			}
		break;
		case 8:
			if (stringIsFinished() == 1) {
				LcGotoXY(0,1);
				LcPutChar('0' + min[1]);
				LcPutChar('0' + min[0]);
				LcPutChar(':');
				LcPutChar('0' + seg[1]);
				LcPutChar('0' + seg[0]);
				state = 1;
			}
		break;
	}
}

void motorModifyTime(void) {
	switch(state_mod) {
		case 0:

		break;
		case 1:
			LcClear();
			LcGotoXY(0,0);
			LcPutString(modifyMsg);
			state_mod = 2;
		break;
		case 2:
			if (stringIsFinished() == 1) {
				LcGotoXY(2,1);
				LcPutChar(':');
				LcGotoXY(0,1);
				i = 0;
				state_mod = 3;
			}
		break;
		case 3:
			if (((getKeyNum() >= 1 && getKeyNum() <= 9) || getKeyNum() == 11) && getKey() != (char) -1) {
                if((getKeyNum() >= 6 && getKeyNum() != 11 && i == 2)) {
                    break;
                }
                
                if(getKeyNum() == 11) {
                    newTime[i] = 0;
                    LcPutChar('0');
                } else {
                    newTime[i] = getKeyNum();
                    LcPutChar(getKeyNum() + '0');
                }
                
                i++;
                if(i == 2) LcPutChar(':');
				state_mod = 4;
			}
		break;
		case 4:
			if (getKey() == (char) -1 && i < 4) {
				state_mod = 3;
			}
			else if (getKey() == (char) -1 && i >= 4) {
				finishedModify = 1;
                LcCursorOff();
				state_mod = 5;
			}
		break;
		case 5:
			if (saveNewTime == 1) {
				min[1] = newTime[0];
				min[0] = newTime[1];
				seg[1] = newTime[2];
				seg[0] = newTime[3];
				state_mod = 0;
			}
		break;
	}
}

void hideModifyTime(){ 
    state_mod = 0;
}

void showModifyTime(){
    state_mod = 1;
    saveNewTime = 0;
    finishedModify = 0;
    LcCursorOn();
}


char getFinishedModify(){
    return finishedModify;
}

void setSaveTime() {
    saveNewTime = 1;
}



void startTime(){
    seg[0] = 0;
    seg[1] = 0;
    min[0] = 0;
    min[1] = 0;
    state = 1;
}

void showCurrentTime(){
    LcCursorOff();
    showTime = 1;
}

void hideCurrentTime(){
    showTime = 0;
}

char* getTimestamp(){
    timestamp[0] = min[1] + '0';
    timestamp[1] = min[0] + '0';
    timestamp[2] = seg[1] + '0';
    timestamp[3] = seg[0] + '0';
    return timestamp;
}