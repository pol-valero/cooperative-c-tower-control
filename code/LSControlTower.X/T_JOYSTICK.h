#ifndef _T_JOYSTICK_H_
#define _T_JOYSTICK_H_

void initJoystick(void);

void motorJoystick(void);

char getGoDown(void);
//Pre: -
//Post: Returns 1 if the screen needs to go down 
//(AND PUTS 0 THE VARIABLE), 0 if not

char getGoUp(void);
//Pre: -
//Post: Returns 1 if the screen needs to go up 
//(AND PUTS 0 THE VARIABLE), 0 if not

void resetMoves(void);
//Pre: -
//Post: Puts 0 in go_up and go_down variables 

#endif