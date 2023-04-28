#ifndef _T_RECORD_H
#define _T_RECORD_H

void initRecord(void);
void motorRecord(void);

void doRecord(void);
//Pre: -
//Post: Activates the record mode

char recordFinished(void);
//Pre: -
//Post: Returns 1 if the record is finished, 0 otherwise

#endif