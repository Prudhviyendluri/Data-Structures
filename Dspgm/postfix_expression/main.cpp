/**************************** main.cpp ****************************/
#include "postfix_exp.h"
using namespace std;	

int main(){
	Postfix_Exp pe; 
	string infix_exp, postfix_exp; 
	while(1){
		try{
			infix_exp.clear(); 
			getline(cin, infix_exp); 
			if(infix_exp.empty()){
				continue; 
			}
			else if(infix_exp == "="){
				pe.set_postfix_exp(postfix_exp); 
				cout << pe.evaluate() << endl;   
			}
			else if(infix_exp == "exit"){
				break; 
			}
			else{
				postfix_exp = Postfix_Exp::infix_to_postfix(infix_exp); 
				cout << postfix_exp << endl; 
			}
		}catch(const exception& e){
			cerr << "Error: " << e.what() << endl; 
		}
	}
	return 0; 
}
