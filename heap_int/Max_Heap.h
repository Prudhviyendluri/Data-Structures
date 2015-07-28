/**************************** Max_Heap.h ****************************/
#ifndef __Max_Heap_H__
#define __Max_Heap_H__

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;  
using std::ostream; 
using std::cout; 
using std::swap;  

/*******************************************************************/
/* Max heap ADT. */
template <class T>
class Max_Heap{
private: 
	vector<T> data;				/* Data stored in vector.   */
	size_t heap_size;			/* No. of elements in heap. */

	/* Utility functions. */
	/* Maintain the heap property by moving the node
	 * at subscript 'index' down the heap. 
	 */
	void heapify_down(size_t index); 

	/* Maintain the heap property by moving the node
	 * at subscript 'index' up the heap. 
	 */
	void heapify_up(size_t index);

	/* Make a heap out of the elements of the vector
	 * associated with this heap. 
	 * Complexity: O(n)
	 */	
	void make_heap(); 

	/* A function similar to pop_heap(); It does not 
	 * delete the node; instead, moves the root node to 
	 * the last location and heapifies the rest of the
	 * elements in vector. This function is useful during
	 * heapsort. (How?)
	 */
	void pop_heap_without_delete(); 

public: 
	/* Constructor: create a heap using a vector, 
	 * given its ranges.  
	 * Complexity: O(n)
	 */
	Max_Heap(
		typename vector<T>::iterator v_begin, 
		typename vector<T>::iterator v_end
	); 
	
	/* Constructor: create a heap using an 
	 * entire vector.   
	 * Complexity: O(n)
	 */
	Max_Heap(vector<T> v); 

	/* Given a heap in the range [first,last-1), this function extends 
	 * the range considered a heap to [first,last) by placing the value 
	 * in (last-1) into its corresponding location within it. 
	 * Complexity: O(log n)
	 */
	void push_heap(T value); 

	/* To delete the root (the max element) and re-heapify. 
	 * Complexity: O(log n) 
	 */
	void pop_heap(); 

	/* Traverse the heap levelorder. 
	 * Complexity: O(n) 
	 */
	void levelorder_traversal(ostream& out = cout) const; 

	/* To print the tree. */
	void print_tree(ostream& out = cout); 

	/* To get the size of the heap. */
	size_t size() const { return heap_size; }; 

	/* To check whether the heap is empty. */
	bool empty()const { return heap_size == 0; }

	/* To get the root element of heap without
	 * removing it from the heap. 
	 */
	T peek() const { return data[1]; }

	/* To get the max element. Same as peek(). */
	T find_max() const { return peek(); }

	/* To get height of heap. */
	int height(){
		return int(log(double(heap_size)) / log(2.0)); 
	}

	/* Static member functions. */
	/* Returns true if the range [first, last) forms a heap. */
	static bool is_heap(
		typename vector<T>::iterator first, 
		typename vector<T>::iterator last
	); 

}; 

/*******************************************************************/
/* Returns true if the range [first, last) forms a heap. */
template<class T>
bool Max_Heap<T>::is_heap(
	typename vector<T>::iterator first, 
	typename vector<T>::iterator last
){
	size_t parent = 0, left = 0, right = 0, size = 0; 
	size = last - first; 
	//cout << "size: " << size << endl; 

	for(parent = 0; parent < size/2; parent++){
		left  = (parent << 1) + 1; 
		right = left + 1; 
		if(((first + left) < last)){
			//cout << "Comparing " << *(first + parent)
			//	 << " and " << *(first + left) << endl; 
			if(*(first+left) > *(first + parent)){
				return false; 
			}
		}

		if(((first + right) < last)){
			//cout << "Comparing " << *(first+parent) 
			//	 << " and " << *(first+right) << endl; 
			if(*(first+right) > *(first+parent)){
				return false; 
			}
		}
	}

	return true; 
}

/*******************************************************************/
#include "Max_Heap.cpp" 

/*******************************************************************/
#endif

/*******************************************************************/
