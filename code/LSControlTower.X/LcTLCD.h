#ifndef LCTLCD_H
#define	LCTLCD_H
//
// ADT for manipulating the alphanumeric display of the 
// HD44780 controller using only 4 data bits.
// This is the controller that almost all displays have integrated. 
// The maximum size is 4 rows and 40 columns.
//
// F. Escudero vCli v1.0 Piera, January of 2004
//
// I have tested this ADT with a 2x16 LCD. If you observe any error please 
// report it to sisco@salleurl.edu.
//
// Vcli V1.1, Sisco, at 26th of November of 2004. I have seen that with som LCD we must wait 2ms
// and after that apply a Clear, independently of what Busy says.
//
// VCli V1.3, jnavarro, a 2013. I have extended the initialization time (now it takes 
// 150 ms. but it is initialized at the first attempt. More info here: 
// http://web.alfredstate.edu/weimandn/lcd/lcd_initialization/lcd_initialization_index.html
// Still observing 
// the same alteration with Busy, except with the timeout.

//
// During the initialization process a timer will be requested from the timer ADT.
//
// ------------------------------------HARDWARE---AREA--------------------
// The connection is of 4 data bits (D4 a D7), and the signals 
// RS, R/W and E.
// In this example we have connected: 
//
// 	RS				to RB3
//	R/!W            to RB15
//  E				to RB5
//	D4				to RB6
//	D5				to RB7
//	D6				to RB8
//	D7				to RB9
//  It is important that the LCD signals D0..D3 are left unused and 
//  that we connect them to GND using resistors. 
//
// 	You can use any configuration that you want modifying the
//  the following defines accordingly
//

#include <xc.h>


#define SetD4_D7Sortida()		(TRISBbits.TRISB6 = TRISBbits.TRISB7 = TRISBbits.TRISB8 = TRISBbits.TRISB9 = 0)
#define SetD4_D7Entrada()		(TRISBbits.TRISB6 = TRISBbits.TRISB7 = TRISBbits.TRISB8 = TRISBbits.TRISB9 = 1)
#define SetControlsSortida()            (TRISBbits.TRISB3 = TRISBbits.TRISB15 = TRISBbits.TRISB5 = 0)
#define SetD4(On)				(LATBbits.LATB6 = (On))
#define SetD5(On)				(LATBbits.LATB7 = (On))
#define SetD6(On)				(LATBbits.LATB8 = (On))
#define SetD7(On)				(LATBbits.LATB9 = (On))
#define GetBusyFlag()                           (PORTBbits.RB9)
#define RSUp()					(LATBbits.LATB3 = 1)
#define RSDown()				(LATBbits.LATB3 = 0)
#define RWUp()					(LATBbits.LATB15 = 1)
#define RWDown()				(LATBbits.LATB15 = 0)
#define EnableUp()				(LATBbits.LATB5 = 1)
#define EnableDown()                            (LATBbits.LATB5 = 0)
// -------------------------------END--HARDWARE---AREA--------------------


void LcInit(char rows, char columns);
// Pre: Rows = {1, 2, 4}  Columns = {8, 16, 20, 24, 32, 40 }
// Pre: There is a free timer
// Pre: It needs 40ms of tranquility between the VCC raising and this constructor being called.
// Post: This routine can last up to 100ms
// Post: The display remains cleared, the cursor turned off and at the position 0, 0.

void LcEnd(void);
// The destructor

void LcClear(void);
// Post: Clears the display and sets the cursor to its previous state. 
// Post: The next order can last up to 1.6ms. 

void LcCursorOn(void);
// Post: Turn on the cursor
// Post: The next order can last up to 40us. 

void LcCursorOff(void);
// Post: Turns off the cursor
// Post: The next order can last up to 40us. 

void LcGotoXY(char Column, char Row);
// Pre : Column between 0 and 39, row between 0 and 3. 
// Post: Sets the cursor to those coordinates. 
// Post: The next order can last up to 40us. 

void LcPutChar(char c);
// Post: Paints the char in the actual cursor position and increments 
// its position. If the column gets to 39 it returns to 0.
// The row of the LCD is increased when this happens until the second
// row and then it is reset back to row 0 if it has 2 rows total. 
// If the LCD has 4 rows it will reset back to row 0 when it
// reaches row 4 and the columns will go till 39 before reseting to 0.
// The one row LCDs returns to 0 when a column gets to 39. 
// The row is never increased. 
	// The char is written

void LcPutString(char *s);
// Post: Paints the string from the actual cursor position. 
// The coordinate criteria is the same as the LcPutChar. 
// Post: Can last up to 40us per char of a routine output.




#endif	/* LCTLCD_H */

