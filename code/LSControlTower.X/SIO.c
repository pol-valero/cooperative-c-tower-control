#include "SIO.h"

#include <xc.h>

void initSIO(void) {
	// Init the SIO and Baudrate
    RCSTAbits.SPEN = 1;
	RCSTAbits.RX9 = 0;
    // Baudrate = 4096 bauds
	SPBRG = 64;					
    TXSTAbits.TXEN = 1;
	RCSTAbits.CREN = 1;
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