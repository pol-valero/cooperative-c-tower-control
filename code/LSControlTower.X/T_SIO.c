#include "T_SIO.h"
#include <xc.h>

void initSIO(void) {
	//Init ports
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    //Init regs & baudcon ())
    TXSTA=0x24; //00100100
    RCSTA=0x90; //10010000
    BAUDCON=0x08; //00001000
    SPBRG=172;
}

char SiCharAvail(void) {
    return (PIR1bits.RCIF == 1? 1 : -1);
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