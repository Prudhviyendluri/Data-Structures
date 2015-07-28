/**************************** Postfix_Exp.h ****************************/
#ifndef __POSTFIX_EXP_H__
#define __POSTFIX_EXP_H__

#include <map>
#include <string> 
#include "Tokenizer.h"
#include <iostream>

/* Debug variable for this class. 
 * Set to 1 for debugged output. 
 */
#define POST_EXP_DBG 0

using std::map; 
using std::string;
using std::operator <<; 
using std::ostream; 

/* Forward declaration. */
class Postfix_Exp; 
ostream& operator << (ostream& out, const Postfix_Exp& exp); 

/* Class to represent a postfix expression. */
class Postfix_Exp{
private:
	/* Static data members. */
	static map<Token_Type, int> precedence_table; 
	static bool init_flag; 
	
	/* Utility functions. */
	void populate_precedence_table(); 
	void init(); 

	/* Postfix expression as a string. */
	string postfix_exp; 

public: 
	/* Default constructor. */
	Postfix_Exp():postfix_exp(""){init(); }
	
	/* Constructor that takes a postfix expression. */
	Postfix_Exp(string pe):postfix_exp(pe){ init(); }

	/* Get and set the postfix expression string. */
	string get_postfix_exp()         { return postfix_exp; }
	void   set_postfix_exp(string pe){ postfix_exp = pe;   }

	/* Function to convert infix to postfix. 
	 * Let us have a static version too so that the convesion 
	 * can also be done without creation of class object. 
	 */
	string set_postfix_from_infix(string infix);
	static string infix_to_postfix(string infix); 

	/* Function to evaluate postfix expression. */
	string evaluate(); 

	/* Friend classes/functions. */
	friend ostream& operator << (ostream& out, const Postfix_Exp& exp); 
}; 

#endif
