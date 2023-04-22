#include <xc.h>
#include <pic18f4321.h>
#include "T_MELODY.h"
#include "T_TIMER.h"

#define TICS_NOTE 1500

static char stateNote;
static char stateMelody;
static unsigned char tmr_melody;
static char note;

void initMelody(void){
    //Init port
    TRISAbits.TRISA2 = 0;
    
    // Create timer
    TI_NewTimer(&tmr_melody);
    
    //Init vars
    stateNote = 0;
    stateMelody = 0;
}

void motorNote(void){
    
}

void motorMelody(void){
    
}

void playNote(char noteNum){
    //Pre: 0 <= noteNum <= 12
    //Post: Play a note 300ms
    note = noteNum;
    stateNote = 1;
}


void playMelody(void){
    stateMelody = 1;
}