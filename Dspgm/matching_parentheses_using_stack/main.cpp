#include "stack.h"
#include <cctype>

using namespace std; 

enum Token_Type {
	EOL,		/* End of Line.			*/
	VALUE,		/* Value.				*/
	LPAREN,		/* Left parenthesis.	*/
	RPAREN,		/* Right parenthesis.	*/
	PLUS,		/* Addition				*/
	MINUS,		/* Subtraction.			*/
	DIV,		/* Division.			*/
	MULT,		/* Multiplication.		*/
	EXP,		/* Exponentiation.		*/
	UNKNOWN		/* Unknown token.		*/
};	

/* Token class. */
template <class T> class Token{
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
		case '(' : return LPAREN; 
		case ')' : return RPAREN; 
		case '\n': return EOL	; 

		default: 
			in.putback(ch); 
			if( in >> value ){
				return Token<T>(VALUE, value); 
			}
			else{
				cin.clear(); 
				cin.ignore(1000, '\n');
				return UNKNOWN; 
			}
		}
	}

	return EOL; 
}

/* Program entry point. */
int main(){
	Stack< Token<int> > stk; 
	Tokenizer<int> tokenizer(cin); 
	bool err_flag = false; 

	while(1){
		cout << "Enter expression: "; cout.flush(); 
		Token<int> curr_token = tokenizer.get_token(); 

		/* Read tokens until end of line. */
		while(curr_token.get_type() != EOL){
			if(curr_token.get_type() == LPAREN){
				stk.push(curr_token); 
			}
			else if(curr_token.get_type() == RPAREN){
				if(stk.empty()){ 
					cerr << "Unbalanced right parenthesis" << endl;
					err_flag = true; 
					cin.ignore(1000, '\n'); 
					break; 
				}
				else{
					/* Remove a corresponding left parenthesis from the stack. */
					stk.pop(); 
				}
			}
			else if(curr_token.get_type() == UNKNOWN){
				cerr << "Parse Error" << endl; 
				err_flag = true; 
				break; 
			}

			/* Get the next token. */
			curr_token = tokenizer.get_token(); 

		} /* while. */

		if(! err_flag){
			cout << (stk.empty() ? "Equal number of LPAREN & RPAREN" : "Unbalanced left parenthesis") << endl; 
		}

		err_flag = false, tokenizer.clear(), stk.clear(); 
	}

	return EXIT_SUCCESS; 
}
