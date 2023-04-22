#include "T_SIO.h"
#include <xc.h>

void initSIO(void) {
	//Init ports
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    
    //Init regs & baudcon ())
    //TXSTA=0x20; //0010 0000
    //RCSTA=0x90; //1001 0000
    //BAUDCON=0;
    //TXSTAbits.BRGH=1;
    //BAUDCONbits.BRG16=0;
    //SPBRG=64;
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