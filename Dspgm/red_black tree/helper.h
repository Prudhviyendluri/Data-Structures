/*********************************** helper.h ****************************************/
#ifndef _HELPER_H_INCLUDED_
#define _HELPER_H_INCLUDED_

/*************************************************************************************/
#include <iostream> 
#include <string> 

/*************************************************************************************/
using namespace std; 

/*************************************************************************************/
#define RED			12
#define YELLOW		14
#define GREEN		10
#define BLUE		9
#define DARK_GREY	8
#define LIGHT_GREY	7
#define VIOLET		5
#define DARK_RED	4
#define DARK_GREEN	2

/*************************************************************************************/
/* Function declrations. */
void	init_color_mode(); 
void	color_print(string msg, int color = RED, int newLineFlag = 0);
void	color_print(int    msg, int color = RED, int newLineFlag = 0);
string	readData(char *dest, int echoON = 1, char c = '*', int color = GREEN);

/*************************************************************************************/
#endif

/*************************************************************************************/