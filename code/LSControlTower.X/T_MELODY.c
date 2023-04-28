#include <xc.h>
#include <pic18f4321.h>
#include "T_MELODY.h"
#include "T_TIMER.h"

#define TICS_NOTE 1500

#define MS_200 800

static char state;

static unsigned char t1;
static unsigned char t2;

static char tone;
static char keyNum;

void initMelody(void){
    //Init port
    TRISAbits.TRISA2 = 0;
    
    // Create timer
    TI_NewTimer(&t1);
    TI_NewTimer(&t2);
    
    //Init vars
    state = 0;
    tone = 0;
    keyNum = (char) -1;
    
}

void motorNote(void){

	switch(state) {
		case 0:

		break;
		case 2:
			TI_ResetTics(t1);
			tone=1;
            LATAbits.LATA2 = 1;
			state = 3;
		break;
		case 3:
			if (TI_GetTics(t1) >= (((keyNum + 1) >> 1) & 0x7F)) {
				tone=0;
                LATAbits.LATA2 = 0;
				state = 4;
			}
		break;
		case 4:
			if (TI_GetTics(t1) >= keyNum) {
				state = 5;
			}
		break;
		case 5:
			if (TI_GetTics(t2) < MS_200) {
				state = 2;
			}
			else if (TI_GetTics(t2) >= MS_200) {
				state = 0;
			}
		break;
		case 1:
			TI_ResetTics(t2);
			state = 2;
		break;
	}
    
}

void motorMelody(void){
    
}

void playNote(char noteNum){
    //Pre: 0 <= noteNum <= 12
    //Post: Play a note 200ms
    keyNum = noteNum;
    state = 1;
}


void playMelody(void){

}