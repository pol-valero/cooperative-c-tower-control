#ifndef _T_RECORD_LIST_H
#define _T_RECORD_LIST_H

#define LIST_SIZE   48

void initRecordList(void);
void motorReadList(void);
void motorWriteList(void);

void saveRecord(char *t, char *id_index);
//Pre: -
//Post: Saves a record in the EEPROM

char* getRecordList();
//Pre: -
//Post: Gets the record list;

char getADRPW();
//Pre: -
//Post: Gets the ADRPW variable

char getNumRecs();
//Pre: -
//Post: Gets the numRecs variable

#endif