#include "T_SIO.h"

#include <xc.h>

void initSIO(void) {
	//TODO: Init the SIO and Baudrate
}

char SiCharAvail(void) {
    return PIR1bits.RCIF;
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