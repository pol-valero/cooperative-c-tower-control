#include <xc.h>
#include <pic18f4321.h>
#include "T_RECORD_LIST.h"

//TODO: DEBUG
//#include "T_LCD.h"

#define ADR_NUM_REC 0x30

static char ADRPW;
static char numRecs;
static char i;
static char recordList[LIST_SIZE];
static char *timestamp;
static char *id;
static char state_w;
static char ADR;


char readROM(char index) {
    EEADR = index;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    return EEDATA;
}



void writeROM(char data, char index) { 
    EEADR = index;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    di();
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    ei();
}

void addData(char data, unsigned char index) {  //TODO: DEBUG
    EEADR = index;
    EEDATA = data;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    
    while (EECON1bits.WR == 1);
    
    EECON1bits.WREN = 0;
}

void initRecordList(){
    //READ INITS
    i = ADR_NUM_REC;
        
    numRecs = readROM(i);
    ADRPW = numRecs & 0x07; 
    state_w = 0;
}

void motorReadList(void) {
	static char state = 1;  //Initially 1!

	switch(state) {
		case 0:

		break;
		case 1:
			if (numRecs >= 8) {
				i = 0;
				state = 3;
			}
			else if (0 < numRecs && numRecs < 8 ) {
				i = 0;
				state = 2;
			}
			else if (numRecs <= 0) {
				state = 0;
			}
		break;
		case 3:
			if (i < 48) {
				recordList[i] = readROM(i);
				i++;
			}
			else if (i >= 48) {
				state = 0;
			}
		break;
		case 2:
			if (i < numRecs * 6) {
				recordList[i] = readROM(i);
				i++;
			}
			else if (i >= numRecs * 6) {
				state = 0;
			}
		break;
	}
}

void motorWriteList(void) {
	switch(state_w) {
		case 0:

		break;
		case 1:
			writeROM(id[i], ADR);
            recordList[ADR] = id[i];
			ADR++;
			i++;
			state_w = 2;
		break;
		case 2:
			if (EECON1bits.WR == 0 && i < 2) {
				EECON1bits.WREN = 0;
				state_w = 1;
			}
			else if (i >= 2 && EECON1bits.WR == 0 ) {
				i = 0;
				EECON1bits.WREN = 0;
				state_w = 3;
			}
		break;
		case 3:
			writeROM(timestamp[i], ADR);
            recordList[ADR] = timestamp[i];
			ADR++;
			i++;
			state_w = 4;
		break;
		case 4:
			if (EECON1bits.WR == 0 && i < 4) {
				EECON1bits.WREN = 0;
				state_w = 3;
			}
			else if ( i >= 4 && EECON1bits.WR == 0) {
				EECON1bits.WREN = 0;
				numRecs++;
				ADRPW = (ADRPW + 1) & 0x07;
				writeROM(numRecs, ADR_NUM_REC);
				state_w = 5;
			}
		break;
		case 5:
			if (EECON1bits.WR == 0) {
				EECON1bits.WREN = 0;
				state_w = 0;
			}
		break;
	}
}

void saveRecord(char *t, char *id_index) {
    timestamp = t;
    id = id_index;
    state_w = 1;
    i = 0;
    ADR = ADRPW * 6;
}

char* getRecordList() {
    return recordList;
}

char getADRPW(){
    return ADRPW;
}

char getNumRecs(){
    return numRecs;
}