#include "Queue_Int.h"
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
void Queue_Int::print(ostream& out) const{
	if(empty()){
		out << "QUEUE EMPTY" << endl; 
	}
	else{
		//out << "f: " << front_queue << " " << "r: " << back_queue << endl; 
		char buf[20]; 
		ostringstream oss; 
		for(Queue_Int::size_type i = 0; i < max_queue_size; i++){
			 int len = string (_itoa(data[i], buf, 10)).size() + 1; 
			 string s1 = "+"+string(len, '-'); 
			 string s2 = s1 + "+"; 
			 //cout << s1 << " and " << s2 << endl; 
			oss << ((i == max_queue_size-1) ? s2 : s1); 
		}
		out << oss.str() << endl; 

		for(Queue_Int::size_type i = 0; i < max_queue_size; i++){
			int len = string (_itoa(data[i], buf, 10)).size() + 1; 
			out << "|" << setw(len) << data[i] << ((i == max_queue_size-1) ? "|" : ""); 
		}
		out << endl; 
		out << oss.str() << endl; 
		oss.str(""), oss.clear(); 

		size_t bigger, smaller; 
		bigger  = max(front_queue, back_queue); 
		smaller = min(front_queue, back_queue); 
				
		string string_with_pipes; 
		string string_with_fr; 

		Queue_Int::size_type i = 0; 
		int len = string (itoa(data[i], buf, 10)).size() + 1; 
		for(i = 0; (i < max_queue_size) && (i < smaller); i++){
			len = string (_itoa(data[i], buf, 10)).size() + 1; 
			//cout << "space added: " << len+1 << endl; 
			oss << string(len+1, ' '); 
		}
		//cout << "i: " << i << endl; 
		if(i == 0){
			oss << string((int)ceil(len/2.0), ' ') << "^" 
				<< string((len/2), ' ');
		}
		else{
			len = string (_itoa(data[i], buf, 10)).size(); 
			oss << string((int)ceil(len/2.0)+1, ' ') 
				<< "^" << string((len-((int)ceil(len/2.0)+1)), ' ');
		}
		i++; 
		
		for(; (i < max_queue_size) && (i < bigger); i++){
			len = string (itoa(data[i], buf, 10)).size() + 1; 
			//out << " " << len+1; 
			oss << string(len+1, ' '); 
		}
		
		if(smaller != bigger){
			len = string (_itoa(data[i], buf, 10)).size(); 
			//cout << len << "(" << i << ")" << endl; 
			oss << string((int)ceil(len/2.0)+1, ' ') << "^";  
		}
		out << oss.str() << endl; 

		string_with_pipes = oss.str(); 
		string_with_fr = oss.str(); 
		string_with_pipes.replace(string_with_pipes.find_first_of('^'), 1, "|"); 
		if(string_with_pipes.find_last_of('^') != -1){
			string_with_pipes.replace(string_with_pipes.find_last_of('^'), 1, "|"); 
		}

		if(front_queue == back_queue){
			string_with_fr.replace(string_with_fr.find_first_of('^'), 1, "f/r"); 
		}
		else if(front_queue < back_queue){
			string_with_fr.replace(string_with_fr.find_first_of('^'), 1, "f"); 
			string_with_fr.replace(string_with_fr.find_last_of('^'), 1, "r"); 
		}
		else{
			string_with_fr.replace(string_with_fr.find_first_of('^'), 1, "r"); 
			string_with_fr.replace(string_with_fr.find_last_of('^'), 1, "f"); 
		}
		out << string_with_pipes << endl; 
		out << string_with_fr << endl; 
		 
		return; 
	}
}

/****************************************************************/

ostream& operator << (ostream& out, const Queue_Int& q){
	q.print(out); 
	return out; 
}

/****************************************************************/

/* Pushing a data into queue. */
void Queue_Int::push(const int& x){
	/* Check if full. */
	if((front_queue == back_queue+1) || 
		((front_queue == 0) && (back_queue == max_queue_size-1))){
		/* Not possible to push, since queue is full. */
		throw std::overflow_error("Queue is full."); 
	}
	else{
		/*	Queue is not full. 
		 * Check whether empty. 
		 */
		if(empty()){
			front_queue = back_queue = 0; 
			data[back_queue] = x; 
		}
		else{
			/* Queue not full. */
			back_queue = ((back_queue == max_queue_size-1) ? 0 : back_queue + 1); 
			data[back_queue] = x; 
		}

		queue_size ++; 
	}/* Queue not full. */
}

/****************************************************************/

/* Popping an element from the queue. */
void Queue_Int::pop(){
	if(empty()){
		throw std::underflow_error("Queue if empty"); 
	}
	else{
		/* Queue not empty. */
		if(size() == 1){
			data[front_queue] = 0; 
			front_queue = back_queue = -1; 
		}
		else{
			/* More than one element. */
			data[front_queue] = 0; 
			front_queue = ((front_queue == max_queue_size-1) ? 0 : front_queue+1); 
		}
		queue_size--; 
	}
}

/****************************************************************/