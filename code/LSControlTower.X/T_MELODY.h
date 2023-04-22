#ifndef _T_MELODY_H
#define _T_MELODY_H

void initMelody(void);
void motorNote(void);
void motorMelody(void);

void playNote(char noteNum);
//Pre: 0 <= noteNum <= 12
//Post: Play a note 300ms

void playMelody(void);
//Pre: -
//Post: Plays the full 8 seconds melody

#endif