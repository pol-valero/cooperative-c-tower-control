#ifndef _T_MENU_H
#define _T_MENU_H

void initMenu(void);
void motorMenu(void);

void showMainMenu(void);
//Pre: -
//Post: Shows the Main Menu through the LCD display

void setTowerName(char* tower);
//Pre: -
//Post: Set the tower name of the harbor

char getTheEnd(void);
//Pre: -
//Post: Gets the_end variable to know if the port has been disconnected

#endif
