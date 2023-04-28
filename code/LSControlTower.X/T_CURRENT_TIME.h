#ifndef _T_CURRENT_TIME_H
#define _T_CURRENT_TIME_H

void initCurrentTime(void);
void motorCurrentTime(void);
void motorModifyTime(void);

void startTime();
//Pre: -
//Post: Resets and starts the time system

void showCurrentTime();
//Pre: -
//Post: Shows the current time of the system

void hideModifyTime();
//Pre: -
//Post: Hides the modify time option desactivating the motor


void hideCurrentTime();
//Pre: -
//Post: Hides the current time of the system

void showModifyTime();
//Pre: -
//Post: Shows the modify time option activating the motor

char getFinishedModify();
//Pre: -
//Post: Gets the finishedModify var. To know if the motor has finished

void setSaveTime();
//Pre: -
//Post: Orders to set the new time into the system

char* getTimestamp();
//Pre: -
//Post: Gets the actual timestamp of the system

#endif
