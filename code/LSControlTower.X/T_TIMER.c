// josepmaria.ribes@salle.url.edu (si hi trobeu alguna errada, si us plau envieu-me un correu :-)
// Arbeca, bressol de l'oliva arbequina
// Mar?, any del Senyor de 2023

// TAD TIMER. Honor i gloria


#include <xc.h>
#include "T_TIMER.h"

#define T0CON_CONFIG 0xC2 //11000010
#define RECARREGA_TMR0 6       

#define TI_NUMTIMERS 8              // Nombre de timers virtuals gestionats per aquest TAD. Si cal, s'incrementa o es disminueix...

// VARIABLES GLOBALS DEL TAD
struct Timer {
	unsigned long TicsInicials;
	unsigned char Busy;
} static Timers[TI_NUMTIMERS];

static volatile unsigned long Tics=0;

void RSI_Timer0 () {
    // Pre: IMPORTANT! Funcio que ha der ser cridada des de la RSI, en en cas que TMR0IF==1.
    TMR0L=RECARREGA_TMR0;   //TODO: Test
    INTCONbits.TMR0IF=0;    //TODO: Test
    Tics++;    
}

// Tinst = 100ns | Ttarget = 200us | PS = 1:8 --> Ttics = 250
// Utilitzant 8bits de timer --> TMR0L = 2^8-250 = 6
void TI_Init () {
	for (unsigned char counter=0; counter<TI_NUMTIMERS; counter++) {
		Timers[counter].Busy=TI_FALS;
	}
	T0CON=T0CON_CONFIG;
    TMR0L=RECARREGA_TMR0;
	INTCONbits.TMR0IF = 0;
	INTCONbits.TMR0IE = 1;
    
    TMR0L=RECARREGA_TMR0;   //TODO: Test
    
    // Caldr? que des del main o des d'on sigui s'activin les interrupcions globals!
}

unsigned char TI_NewTimer(unsigned char *TimerHandle) {
	unsigned char Comptador=0;
	while (Timers[Comptador].Busy==TI_CERT) {
		if (++Comptador == TI_NUMTIMERS) return (TI_FALS);
	}
	Timers[Comptador].Busy=TI_CERT;
	*TimerHandle=Comptador;
    return (TI_CERT);
}

void TI_ResetTics (unsigned char TimerHandle) {
	di(); Timers[TimerHandle].TicsInicials=Tics; ei();
}


unsigned long TI_GetTics (unsigned char TimerHandle) {
    di(); unsigned long CopiaTicsActual=Tics; ei();
	return (CopiaTicsActual-(Timers[TimerHandle].TicsInicials));
}

void TI_CloseTimer (unsigned char TimerHandle) {
	Timers[TimerHandle].Busy=TI_FALS;
}

void TI_End () {
}