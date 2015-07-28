#include "Queue_doubly_Linked_List.h"
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include <sstream>

using namespace std; 

/****************************************************************/

/* To print the queue. */
template<class type>
void Queue_doubly_Linked_List<type>::print(ostream& out) const{
	if(empty()){
		out << "QUEUE EMPTY" << endl; 
	}
	else{
		ostringstream oss; 
		for(typename List_doubly_linked<type>::size_type i = 0; i < data.size(); i++){
			int len = 5; 
			string s1 = "+"+string(len, '-'); 
			string s2 = s1 + "+"; 
			oss << ((i == data.size()-1) ? s2 : s1); 
		}
		out << oss.str() << endl; 

		int counter = 0; 
		for(typename List_doubly_linked<type>::iterator i = data.begin(); i != data.end(); i++){
			counter++; 
			int len = 5; 
			out << "|" << setw(len) << *i; 
		}
		
		out << "|" << endl; 
		out << oss.str() << endl; 
		oss.str(""), oss.clear(); 

		string string_with_pipes; 
		string string_with_fr; 

		typename List_doubly_linked<type>::size_type i = 0; 
		int len = 5; 
		oss << string((int)ceil(len/2.0), ' ') << "^" 
				<< string((len/2), ' ');
		i++; 
		
		for(; i < data.size()-1; i++){
			len = 5; 
			oss << string(len+1, ' '); 
		}
		
		if(data.size() != 1){
			len = 5; 
			oss << string((int)ceil(len/2.0)+1, ' ') << "^";  
		}
		out << oss.str() << endl; 

		string_with_pipes = oss.str(); 
		string_with_fr = oss.str(); 
		string_with_pipes.replace(string_with_pipes.find_first_of('^'), 1, "|"); 
		if(string_with_pipes.find_last_of('^') != -1){
			string_with_pipes.replace(string_with_pipes.find_last_of('^'), 1, "|"); 
		}

		if(data.size() == 1){
			string_with_fr.replace(string_with_fr.find_first_of('^'), 1, "f/r"); 
		}
		else{
			string_with_fr.replace(string_with_fr.find_first_of('^'), 1, "f"); 
			string_with_fr.replace(string_with_fr.find_last_of('^'), 1, "r"); 
		}

		out << string_with_pipes << endl; 
		out << string_with_fr << endl; 
		 
		return; 
	}
}

/****************************************************************/
template<class type>
ostream& operator << (ostream& out, const Queue_doubly_Linked_List<type>& q){
	q.print(out); 
	return out; 
}

/****************************************************************/

/* Pushing a data into queue. */
template<class type>
void Queue_doubly_Linked_List<type>::push(const type& x){
	data.push_back(x); 
}

/****************************************************************/

/* Popping an element from the queue. */
template<class type>
void Queue_doubly_Linked_List<type>::pop(){
	data.pop_front(); 
}

/****************************************************************/