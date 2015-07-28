#include "Queue_Int.h"
#include <string>

using namespace std; 

int main(){
	Queue_Int q; 
	string cmd; 
	int data; 

	while(1){
		try{
			cin >> cmd; 
			     if(cmd == "push" ) cin >> data; 
				 if(cmd == "push" ) q.push(data); 
			else if(cmd == "pop"  ) q.pop(); 
			else if(cmd == "print") cout << q << endl; 
			else if(cmd == "front") cout << q.front() << endl; 
			else if(cmd == "back" ) cout << q.back() << endl; 
			else if(cmd == "exit" ) break; 
			else                    cerr << "Wrong command" << endl; 
		}catch(const overflow_error& e){
			cerr << e.what() << endl; 
		}catch(const underflow_error& e){
			cerr << e.what() << endl; 
		}
	}

	return 0; 
}
