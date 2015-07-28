/**************************** Max_Heap.cpp **************************/
#include "Max_Heap.h"
#include <cassert>
#include <iomanip>

using std::swap; 
using std::floor; 
using std::setw; 

/*******************************************************************/
/* Constructor: create a heap using a vector, given its ranges.  
 * Complexity: O(n)
 */
template<class T>
Max_Heap<T>::Max_Heap(
	typename vector<T>::iterator v_begin, 
	typename vector<T>::iterator v_end
){
	/* Make sure there is at least one element in the vector. */
	assert((v_end - v_begin) > 0); 

	/* Starting index is 1. 
	 * Index location 0 is left free. 
	 */
	data.push_back(0); 
	size_t v_size = v_end - v_begin; 
	for(vector<T>::iterator itr = v_begin; itr != v_end; itr++){
		data.push_back(*itr); 
	}

	/* Set heap size. */
	heap_size = v_size; 

	/* Now heapify using Floyd's heap creation algorithm. 
	 * Complexity: O(n)
	 */
	make_heap(); 
}

/*******************************************************************/
/* Constructor: create a heap using an entire vector.   
 * Complexity: O(n)
 */
template<class T>
Max_Heap<T>::Max_Heap(vector<T> v){
	/* Make sure there is at least one element in the vector. */
	assert(v.size() > 0); 

	/* Starting index is 1. 
	 * Index location 0 is left free. 
	 */
	data.push_back(0); 
	size_t v_size = v.end() - v.begin(); 
	for(vector<T>::iterator itr = v.begin(); itr != v.end(); itr++){
		data.push_back(*itr); 
	}

	/* Set heap size. */
	heap_size = v_size; 

	/* Now heapify using Floyd's heap creation algorithm. 
	 * Complexity: O(n)
	 */
	make_heap(); 
}

/*******************************************************************/
/* Make a heap out of the elements of the vector associated with
 * this heap. Assumes index starts from 1. 
 * Complexity: O(n)
 */
template<class T>
void Max_Heap<T>::make_heap(){
	/* Heapify using Floyd's heap creation algorithm. 
	 * Complexity: O(n)
	 */
	     if(data.size() <= 1) return; 
	else
	for(size_t i = (data.size()/2); i >= 1; i--){
		heapify_down(i); 
	}
}

/*******************************************************************/
/* Move the node with index 'i' down such that the heap property 
 * is maintained. This operation is done during deletion (of root)
 * and during heap creation. 
 * 
 * 1. Compare the node with its children.
 * 2. If they are in the correct order, stop. 
 * 3. If not, swap the element with the largest child 
 * 4. Return to step 1. 
 * 
 */
template<class T>
void Max_Heap<T>::heapify_down(size_t index){
	assert(index <= heap_size); 
	size_t left    = (index << 1);		/* Mul by 2.				*/
	size_t right   = (index << 1) + 1;	/* Mul by 2; then add 1.	*/
	size_t largest = index;			

	if((left <= heap_size) && (data[left] > data[largest])){ 
		largest = left; 
	}

	if((right <= heap_size) && (data[right] > data[largest])){
		largest = right; 
	}

	if(largest != index){
		swap(data[index], data[largest]); 
		heapify_down(largest); 
	}
}

/*******************************************************************/
/* Move the node with index 'i' up such that the heap property 
 * is maintained. This operation is used during insertion of a 
 * new node. 
 */
template<class T>
void Max_Heap<T>::heapify_up(size_t index){
	assert(index <= heap_size); 
	size_t parent = index / 2; 

	if(data[index] > data[parent]){
		swap(data[index], data[parent]); 
		heapify_up(parent); 
	}

	return; 
}

/*******************************************************************/
/* Traverse the heap levelorder. 
 * Complexity: O(n)
 */
template<class T>
void Max_Heap<T>::levelorder_traversal(ostream& out = cout) const {
	for(size_t i = 1; i < data.size(); i++){
		out << data[i] << " "; 
	}
	out << endl; 
}

/*******************************************************************/
/* Given a heap in the range [first,last-1), this function extends 
 * the range considered a heap to [first,last) by placing the value 
 * in (last-1) into its corresponding location within it. 
 * Complexity: O(log n)
 */
template<class T>
void Max_Heap<T>::push_heap(T value){
	data.push_back(value); 
	heap_size++; 
	heapify_up(heap_size); 
	return; 
}

/*******************************************************************/
/* To delete the root (the max element) and re-heapify. 
 * Complexity: O(log n)
 */
template<class T>
void Max_Heap<T>::pop_heap(){
	assert(! empty()); 
	if(heap_size == 1){
		/* Only one element left in heap. */
		heap_size = 0; 
		data.clear(); 
	}
	else{
		/* More than one element left in heap. */
		data[1] = data[heap_size]; 
		--heap_size; 
		data.pop_back(); 
		heapify_down(1); 
	}
}

/*******************************************************************/
/* To print the tree. */
template<class T>
void Max_Heap<T>::print_tree(ostream &out){
	out << endl; 

	size_t h = height(); 

	vector<size_t> spaces; 
	spaces.push_back(0); 
	for(size_t i = 0; i <= h; i++){
		spaces.push_back((spaces[i]+1) * 2); 
	}
	reverse(spaces.begin(), spaces.end()); 
	for(size_t i = 0; i < spaces.size(); i++){
		out << spaces[i] << " " ; 
	}
	out << endl;

	size_t counter = 1; 
	for(size_t i = 0; i <= h; i++){ /* No. of levels. */
		for(size_t k = 0; k < pow(2.0, i*1.0); k++){ /* No. of nodes in one level. */
			if(counter > heap_size) break; 

			/* Spaces before num. */
			for(size_t j = 0; j < spaces[i]; j++) out << ' '; 
			
			/* Printing num. */
			out << setw(3) << data[counter++]; 

			/* Printing spaces after num. */
			for(size_t j = 0; j < spaces[i]+1; j++) out << ' '; 
		}
		out << endl;

		if(counter > heap_size) break; 

		/* Printing arrows. */
		size_t count_1 = spaces[i], count_2 = 0, count_3 = 1;  
		for(size_t j = 0; j < spaces[i]/2; j++){	/* No. of lines. */
			
			for(size_t k = 0; k < pow(2.0, i*1.0); k++){	/* No. of arrows per level. */
				/* Spaces before left arrow. */
				for(size_t l = 0; l < count_1-count_3; l++) out << ' '; 

				/* Left arrow. */
				out << "/";  
				
				/* Spaces between left and right arrows. */
				for(size_t l = 0; l < 3+count_2; l++) out << ' '; 

				/* Right arrow. */
				out << "\\"; 

				/* Spaces after right arrow. */
				for(size_t l = 0; l < count_1-count_3; l++) out << ' '; 

				/* The extra one space. */
				out << " "; 
			}
			out << endl;
			count_2 += 2;
			count_3 ++; 
		} 
	}
	out << endl; 
}

/*******************************************************************/