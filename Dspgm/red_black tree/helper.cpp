/************************************ helper.cpp *************************************/
#include <windows.h>
#include <conio.h>
#include "helper.h"
#include <cstdlib>
#include <cassert> 

/*************************************************************************************/
using namespace std; 

/*************************************************************************************/
/* Win32 API - variables. */
HANDLE							hStdOut					;
WORD							wOldColorAttrs			;
CONSOLE_SCREEN_BUFFER_INFO		csbiInfo				;

/*************************************************************************************/
void init_color_mode(){
	/* Saving windows current text colors. */
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE)	;
	GetConsoleScreenBufferInfo(hStdOut, &csbiInfo); 
	wOldColorAttrs = csbiInfo.wAttributes;
}

/*************************************************************************************/
/* Description	: Function to print a given message in a specific colour. 
 * Arguments	: msg			: C string message that has to be printed. 
 *				  color			: The color in which it has to be printed. 
 *				  newLineFlag	: 1 indicates '\n' has to be appended to the message. 
 *								  0 indicates '\n' need not be appended. 
 * Return Values: None. 
 * 
 * Changing text color in Windows console mode; 
 * Colors are 0=black 1=blue 2=green 4=red and so on to 15=white  
 * colorattribute = foreground + background * 16
 * 
 * Eg. To get red text on yellow, use 4 + 14*16 = 228
 * Eg. To get light red on yellow, use 12 + 14*16 = 236
 * 
 */
void color_print(string msg, int color, int newLineFlag){
	SetConsoleTextAttribute(hStdOut, color + 0 * 16); 
	if(newLineFlag) cout << msg << endl; 
	else			cout << msg; 
	SetConsoleTextAttribute(hStdOut, wOldColorAttrs); 
	
	return; 
}

void color_print(int msg, int color, int newLineFlag){
	SetConsoleTextAttribute(hStdOut, color + 0 * 16); 
	if(newLineFlag) cout << msg << endl; 
	else			cout << msg; 
	SetConsoleTextAttribute(hStdOut, wOldColorAttrs); 
	
	return; 
}
/*************************************************************************************/

/* Description	: Function to read data from the user (character wise) and store in a string.
 *				  Stops reading when the newline character is encountered. 
 *				  Newline is not part of the the final string and is not echoed on the screen. 
 *				  The function takes care of the backspace characters typed by the user. 
 * Arguments	: dest	: The pointer to the location where the string will be saved. 
 *				  echoOn:  1 indicates that the typed chracters will be echoed.  
 *						   0 indicated that the typed characters will not be echoed. 
 *						  -1 indicates that 'c' will be displayed for each typed characters. 
 *				  color	: if echoOn is 1 or -1, then the characters are displayed in the 
 *					      specified color on black background. 
 * Return value	: 'dest'
 */

string& readData(string &dest, int echoON, char c, int color){
	dest.reserve(100); 
	char cTemp = 0;
	int	 iTemp = 0;
	
	SetConsoleTextAttribute(hStdOut, color + 0 * 16);
	dest[0] = 0;
	iTemp   = 0;
	while((cTemp = _getch()) != 13){
		if(cTemp != '\b'){
			dest[iTemp++] = cTemp;
		}
		else{
			/* The user typed a backspace character. */
			if(((echoON == 1) || (echoON == -1)) && (iTemp > 0)){
				putchar('\b'), putchar(' '), putchar('\b');
				iTemp--;
			}
		}

		/* Echoing of character. */
		if(cTemp != '\b'){
			assert((echoON == 1) || (echoON == -1) || (echoON == 0)); 
			if(echoON == 1){
				putchar(cTemp);
			}
			else if(echoON == -1){
				putchar(c);
			}
		}
	}
	dest[iTemp] = 0;
	SetConsoleTextAttribute(hStdOut, wOldColorAttrs);
	return dest;	
}

/*************************************************************************************/
