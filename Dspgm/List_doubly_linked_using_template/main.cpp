#include "List_doubly_linked.h"
#include <list>
#include <string>

using namespace std; 

/* Program entry point. */
int main(){
	List_doubly_linked<string> l1; 

	l1.push_back("Apple"); 
	l1.push_back("Mango"); 
	l1.push_front("Kiwi"); 
	l1.print(); 
	cout << l1.size() << endl; 
	List_doubly_linked<string>::iterator itr = l1.begin(); 
	itr++, itr++; 
	l1.insert(itr, "Guava"); 
	l1.print(); 
	l1.insert(l1.end(), "Pineapple"); 
	l1.print(); 
	itr = l1.end(); 
	itr--; 
	l1.insert(itr, "Banana"); 
	l1.insert(l1.begin(), "Gooseberry"); 
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

