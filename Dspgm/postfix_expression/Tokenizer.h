/**************************** Tokenizer.h ****************************/
#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <cctype>

enum Token_Type {
	EOL,		/* End of Line.			*/
	VALUE,		/* Value.				*/
	PLUS,		/* Addition				*/
	MINUS,		/* Subtraction.			*/
	DIV,		/* Division.			*/
	MULT,		/* Multiplication.		*/
	EXP,		/* Exponentiation.		*/
	MOD,		/* Modulus.				*/
	LPAREN,		/* Right parenthesis.	*/
	RPAREN,		/* Left parenthesis.	*/
	UNKNOWN		/* Unknown token.		*/
};	

/* Token class. */
template <class T>
class Token{
private:
	Token_Type	token_type	; 
	T			token_value	; 

public:
	Token(Token_Type tt = EOL, const T& val = 0)
		:token_type(tt), token_value(val){}

	Token_Type get_type () const { return token_type;  }
	const T&   get_value() const { return token_value; } 
}; 

/* Tokenizer class. */
template <class T>
class Tokenizer{
private:
	std::istream& in; 

public:
	Tokenizer(std::istream& is) : in(is){}
	Token<T> get_token(); 
	void clear(){ in.clear(); }
}; 

/* Find the next token, skipping blanks and return it. */
template <class T>
Token<T> Tokenizer<T>::get_token(){
	char ch   ; 
	T    value; 

	/* Skip blanks. */
	while(in.get(ch) && ((ch == ' ') || (ch == '\t')) )
		; 
	if(in.good()){
		switch(ch){
		case '^' : return EXP	; 
		case '/' : return DIV	; 
		case '*' : return MULT	; 
		case '+' : return PLUS	; 
		case '-' : return MINUS	; 
		case '%' : return MOD	; 
		case ')' : return RPAREN; 
		case '(' : return LPAREN; 
		case '\n': return EOL	; 
		case '\0': return EOL   ; 

		default: 
			in.putback(ch); 
			if(in >> value){
				return Token<T>(VALUE, value); 
			}
			else{
				cin.clear(); 
				return UNKNOWN; 
			}
		}
	}
	else{
		//cout << "Stream error" << endl; 
	}

	return EOL; 
}

#endif
