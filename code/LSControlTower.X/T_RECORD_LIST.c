#include <xc.h>
#include <pic18f4321.h>

//TODO: DEBUG
#include "T_LCD.h"

#define ADR_NUM_REC 48
#define LIST_SIZE   48

static char ADRPW;
static char ADRPR;
static char numRecs;
static char i;
static char data;
static char recordList[LIST_SIZE];

char readROM(char index) {
    EEADR = index;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    data = EEDATA;
    EECON1bits.RD = 0;
    return data;
    //return EEDATA;
}

void addData(char data, unsigned char index) {  //TODO: DEBUG
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
    while (EECON1bits.WR == 1);

    EECON1bits.WREN = 0;
}

void initRecordList(){
    //READ INITS
    i = ADR_NUM_REC;
    
    addData((char) 3, (unsigned char) 48);
    
    numRecs = readROM(48);
    
    
    
    LcGotoXY(0,0);
    LcPutChar(numRecs + '0');
    
    ADRPW = numRecs & 0x08; 
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
			else if (0 < numRecs && numRecs < 8) {
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
			state = 0;
		break;
		case 2:
			if (i < numRecs * 6) {
				recordList[i] = readROM(i);
				i++;
			}
			state = 0;
		break;
	}
}

void motorWriteList(){

}