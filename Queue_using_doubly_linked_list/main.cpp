#include "Queue_doubly_Linked_List.h"
#include <string>

using namespace std; 


int main(){
	Queue_doubly_Linked_List<int> q; 
	string cmd; 
	int data; 

	while(1){
		try{
			cin >> cmd; 
			     if(cmd == "push"     ) cin >> data; 
				 if(cmd == "push"     ) q.push(data); 
			else if(cmd == "pop"      ) q.pop(); 
			else if(cmd == "size"     ) cout << q.size() << endl; 
			else if(cmd == "print"    ) cout << q << endl; 
			else if(cmd == "front"    ) cout << q.front() << endl; 
			else if(cmd == "set_front") cin >> data, q.front() = data; 
			else if(cmd == "set_back" ) cin >> data, q.back() = data; 
			else if(cmd == "back"     ) cout << q.back() << endl; 
			else if(cmd == "exit"     ) break; 
			else                    cerr << "Wrong command" << endl; 
		}
		catch(const overflow_error& e) { cerr << e.what() << endl; }
		catch(const underflow_error& e){ cerr << e.what() << endl; }
	}

	return 0; 
}
