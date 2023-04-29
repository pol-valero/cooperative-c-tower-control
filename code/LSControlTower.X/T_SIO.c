#include "T_SIO.h"
#include <xc.h>

void initSIO(void) {
	//Init ports
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    //BAUDRATE: 115200
    //Init regs & baudcon
    TXSTA=0x24; //00100100
    RCSTA=0x90; //10010000
    BAUDCON=0x08; //00001000
    SPBRG=34;
}

char SiCharAvail(void) {
    if(PIR1bits.RCIF == 1) {
        return 1;
    } else {
        return -1;
    }
}

char SiGetChar(void) {
    return RCREG;
}

char SiIsAvailable(void) {
	return TXSTAbits.TRMT;
}

void SiSendChar(char c) {
	TXREG = c;
}