#ifndef _T_KEYPAD_H
#define _T_KEYPAD_H

void initKeypad(void);
void motorKeypad(void);

char getKey(void);
//Pre: -
//Post: Returns the key that is being pressed, -1 if no key is pressed

char getKeyNum(void);
//Pre: -
//Post: Returns the index of the key that is being pressed, -1 if no key is pressed

void resetIndexSMS(void);
//Pre: -
//Post: Equals to 0 in the indexSMS variable

#endif

