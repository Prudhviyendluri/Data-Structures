#include "List_double_ptr_Int.h"
#include <list>

using namespace std; 

/* Program entry point. */
int main(){
	List_double_ptr_Int l1; 

	l1.push_back(10); 
	l1.push_back(20); 
	l1.push_front(30); 
	l1.print(); 
	cout << l1.size() << endl; 
	List_double_ptr_Int::iterator itr = l1.begin(); 
	itr++, itr++; 
	l1.insert(itr, -10); 
	l1.print(); 
	l1.insert(l1.end(), -20); 
	l1.print(); 
	itr = l1.end(); 
	itr--; 
	l1.insert(itr, -40); 
	l1.insert(l1.begin(), -50); 
	l1.print(); 
	cout << l1.size() << endl ;
	itr--, itr--, itr--; 
	cout << *itr << endl; 
	l1.erase(l1.begin(), itr); 
	l1.print(); 
	itr = l1.end(); 
	itr--, itr--; 
	cout << *(l1.erase(itr)) << endl; 
	l1.print(); 
	

	return EXIT_SUCCESS; 
}

