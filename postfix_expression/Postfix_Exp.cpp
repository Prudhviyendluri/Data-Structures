/**************************** Postfix_Exp.cpp ****************************/
#include "postfix_exp.h"
#include <iostream>
#include "Tokenizer.h"
#include "stack.h"
#include <sstream>
#include "Queue_doubly_Linked_List.h"
#include <cassert> 

using std::pair; 
using std::cout; 
using std::endl; 
using std::istringstream; 

/* Static member definition. */
map<Token_Type, int> Postfix_Exp::precedence_table; 
bool                 Postfix_Exp::init_flag = false; 

/* Populate the precedence table. */
void Postfix_Exp::populate_precedence_table(){
	precedence_table.insert(pair<Token_Type, int>(PLUS , 1)); 
	precedence_table.insert(pair<Token_Type, int>(MINUS, 1)); 
	precedence_table.insert(pair<Token_Type, int>(MULT , 2)); 
	precedence_table.insert(pair<Token_Type, int>(DIV  , 2)); 
	precedence_table.insert(pair<Token_Type, int>(MOD  , 2)); 
	precedence_table.insert(pair<Token_Type, int>(EXP  , 3));
}

/* Initializing class. */
void Postfix_Exp::init(){
	if(init_flag == false){
		init_flag = true; 
		populate_precedence_table(); 
	}
}

/* Function to convert infix to postfix. */
string Postfix_Exp::set_postfix_from_infix(string infix){
	this->postfix_exp = infix_to_postfix(infix); 
	return this->postfix_exp; 
}

/* To print the postfix expression. */
ostream& operator << (ostream& out, const Postfix_Exp& exp){
	out << exp.postfix_exp; 
	return out; 
}

/* Static function to convert infix to postfix. */
string Postfix_Exp::infix_to_postfix(string infix){
	if(POST_EXP_DBG) cout << "Converting " << infix 
						  << " to postfix" << endl; 
	typedef int data_type; 
	typedef Token<data_type> token_type; 
	token_type curr_token; 
	Stack<token_type> stk; 
	Queue_doubly_Linked_List<token_type> queue; 

	/* Push '(' onto stack and ')' to the end of infix expression. */
	stk.push(Token<int>(LPAREN)); 
	infix.append(")"); 
	istringstream iss(infix); 
	Tokenizer<data_type> tokenizer(iss); 

	/* Start scanning the infix expression from left to right. */
	curr_token = tokenizer.get_token(); 
	while((!stk.empty()) && (curr_token.get_type() != EOL)){
		if(curr_token.get_type() == VALUE){
			/* Operand detected; add it to queue. */
			if(POST_EXP_DBG) cout << "Pushing VALUE to queue " << endl; 
			queue.push(curr_token); 
		}
		else if(curr_token.get_type() == LPAREN){
			/* Left parenthesis detected; push to stack. */
			if(POST_EXP_DBG) cout << "Pushing LPAREN to stack" << endl; 
			stk.push(curr_token); 
		}
		else if(curr_token.get_type() == RPAREN){
			/* Left parenthesis detected. 
			 * Repeatedly pop from the stack and add to queue
			 * each operator until a right parenthesis is encountered. 
			 * And then remove '(' from stack. 
			 */
			if(POST_EXP_DBG) cout << "Detected RPAREN" << endl; 
			token_type top_token = stk.top(); 
			while( (!stk.empty()) && (top_token.get_type() != LPAREN)){
				queue.push(top_token); 
				stk.pop(); 
				top_token = stk.top(); 
			}

			/* If stack is empty, then there is an error in the
			 * infix expression. There is extra ')'. 
			 */
			if(stk.empty()){ throw runtime_error("Unmatched Right Parenthesis. "); }
			else{
				/* Removing '(' from the stack. */
				if(POST_EXP_DBG) cout << "Removing '(' from the stack. " << endl; 
				stk.pop(); 
			}
		}
		else if(curr_token.get_type() == UNKNOWN){
			if(POST_EXP_DBG) cout << "Unknown token detected" << endl; 
			throw runtime_error("Unknown token detected."); 
		}
		else{
			/* Operator. */
			/* Repeatedly pop from the stack and add to queue
			 * each operator which has the same precedence or higher
			 * precedence as this operator and then add the current
			 * token to the stack. 
			 */
			if(POST_EXP_DBG) cout << "Possibly operator" << endl; 
			while(!stk.empty()){
				token_type top_token = stk.top(); 
				/* If you find a '(', you can break out of the stack. */
				if(top_token.get_type() == LPAREN){
					break; 
				}

				/* Make sure the the token is present in the 
				 * precedence table. */
				if(precedence_table.count(curr_token.get_type()) == 0){
					throw runtime_error("Unknown token detected in input. "); 
				}

				if(precedence_table[top_token.get_type()] >= 
					precedence_table[curr_token.get_type()]
				){
					stk.pop(); 
					queue.push(top_token); 
					if(POST_EXP_DBG) cout << "pushing token to queue: " 
										  << top_token.get_type() << endl; 
				}
				else{
					/* Found an operator on top of stack with lower
					 * precedence than the current operator. 
					 */
					break; 
				}
			} /* while(!stk.empty()){ ... } */

			/* Add current token on to the stack. */
			stk.push(curr_token); 
		} /* Operator. */

		/* Get the next token from the input. */
		curr_token = tokenizer.get_token(); 

	} /* while((!stk.empty()) && (curr_token.get_type() != EOL)){ ... } */

	/* If stack is not empty, or if there are still tokens 
	 * left to process, then it's an error. 
	 */
	if((! stk.empty()) || (curr_token.get_type() != EOL)){
		throw runtime_error("Improper infix expression"); 
	}

	/* The stream of tokens in the queue represents the postfix expression. 
	 * Convert it into a string. 
	 */
	string postfix; 
	if(POST_EXP_DBG) cout << "Creating string from queue of tokens" << endl; 
	while(! queue.empty()){
		Token<int> tok = queue.front(); 
		if(tok.get_type() == PLUS) postfix.append("+ "); 
		else if(tok.get_type() == MINUS) postfix.append("- "); 
		else if(tok.get_type() == DIV) postfix.append("/ "); 
		else if(tok.get_type() == MULT) postfix.append("* "); 
		else if(tok.get_type() == EXP) postfix.append("^ "); 
		else if(tok.get_type() == MOD) postfix.append("% "); 
		else if(tok.get_type() == VALUE){
			/* Operand in queue. */
			char c_buffer[100]; 
			_itoa(tok.get_value(), c_buffer, 10); 
			string s_temp(c_buffer); 
			postfix.append(s_temp + " "); 
		}
		else{
			/* Unknown token. */
			throw runtime_error("Unknown token in queue"); 
		}
		
		queue.pop(); 
	} /* while(! queue.empty()){ ... } */

	return postfix;
}

/* Function to evaluate postfix expression. */
string Postfix_Exp::evaluate(){
	typedef int					data_type		; 
	typedef	Token<data_type>	token_type		; 
	Token<data_type>			curr_token		; 
	Stack <token_type>			stk				; 
	bool						err_flag = false; 
	data_type					temp_result		; 
	token_type					op1				; 
	token_type					op2				; 
	token_type					final_answer	; 

	string temp_pe(this->postfix_exp); 
	istringstream				iss(temp_pe); 
	Tokenizer<data_type>		tokenizer(iss)	; 
	while(1){
		err_flag = false; 
		stk.clear(); 
		curr_token = tokenizer.get_token() ;
		while(curr_token.get_type() != EOL){
			switch(curr_token.get_type()){
			case VALUE: 
				stk.push(curr_token); 
				break; 

			case MULT : 
			case DIV  : 
			case PLUS : 
			case MINUS: 
			case EXP  : 
			case MOD  : 
				if(stk.size() >= 2){
					/* Get the top two items from the stack. */
					op1 = stk.top(), stk.pop(); 
					op2 = stk.top(), stk.pop(); 

					/* Find the result, using the current token operator. */
					temp_result = 
						(curr_token.get_type() == MULT ) ? (op2.get_value() * op1.get_value()) :  
						(curr_token.get_type() == DIV  ) ? (op2.get_value() / op1.get_value()) : 
						(curr_token.get_type() == PLUS ) ? (op2.get_value() + op1.get_value()) : 
						(curr_token.get_type() == MOD  ) ? (op2.get_value() % op1.get_value()) : 
						(curr_token.get_type() == EXP  ) ? 
									 ((data_type)pow(op2.get_value()*1.0, op1.get_value()*1.0)): 
						0; 

					/* Push the result back to stack. */
					stk.push(Token<data_type>(VALUE, temp_result)); 
				}
				else{
					err_flag = true; /* Error. */
				}
				break; 

			case UNKNOWN: 
				throw runtime_error("Parse error"); 
				break; 
			}/* switch. */

			if(err_flag) break; 

			/* Fetch the next token. */
			curr_token = tokenizer.get_token(); 
		}/* while. */

		if(!err_flag){
			if(stk.size() == 1){
				final_answer = stk.top(); 
				char c_buffer[100]; 
				_itoa(final_answer.get_value(), c_buffer, 10); 
				string s_temp(c_buffer); 
				return s_temp; 
			}
		}
		else{
			tokenizer.clear();
			throw runtime_error("Improper postfix expression"); 
		}	
	}
}
