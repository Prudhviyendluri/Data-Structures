/**************************** main.cpp *****************************/
#include "Max_Heap.h"
#include <vector>

using namespace std; 

/*******************************************************************/
/* Sorting using heapsort. */
template <class T>
void heap_sort(
	typename vector<T>::iterator start, 
	typename vector<T>::iterator end
){
	typename vector<T>::iterator st = start; 
	Max_Heap<T> temp_heap(start, end); 

	while(! temp_heap.empty()){
		*st = temp_heap.peek(); 
		st++; 
		temp_heap.pop_heap(); 
	}
}

/*******************************************************************/
/* Program entry point. */
int main(){
	int ints[] = { 20, 30, 10, 9, 8, 7, 6, 11, 9, 17, 18, 19 }; 
	vector<int> v(ints, ints + (sizeof(ints) / sizeof(int)) ); 

	/* Input data. */
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " "; 
	}
	cout << endl; 

	/* Check whether the vector represents a valid heap. */
	cout << "Checking whether the input vector represents a heap: " << endl; 
	if(Max_Heap<int>::is_heap(v.begin(), v.end())){
		cout << "Yes; it is heap" << endl; 
	}
	else{
		cout << "No; it is not a heap" << endl; 
	}
	cout << endl; 

	/* Creating a heap. */
	cout << "Creating a heap" << endl; 
	Max_Heap<int> heap_1(v); 
	cout << "Level-order traversal of heap: ", heap_1.levelorder_traversal(); 
	cout << "\nPrinting heap: " << endl		 , heap_1.print_tree(); 

	/* Getting the height of heap. */
	cout << "Heap height        : " 
		 << heap_1.height() << endl; 

	/* Getting the max element. */
	cout << "Max element is     : " 
		 << heap_1.find_max() << endl; 

	/* Inserting a node. */
	heap_1.push_heap(5); 
	cout << "After inserting 5  : "; 
	heap_1.print_tree(); 

	/* Delete the root. */
	heap_1.pop_heap(); 
	cout << "After deleting root: "; 
	heap_1.print_tree(); 

	/* Sorting using heapsort. */
	cout << "Heapsorting        : "; 
	heap_sort<int>(v.begin(), v.end()); 

	/* Printing the sorted array. */
	for(size_t i = 0; i < v.size(); i++){
		cout << v[i] << " "; 
	}
	cout << endl; 

	/* Deleting 3 elements. */
	heap_1.pop_heap(), heap_1.pop_heap(); 
	heap_1.pop_heap(); 
	cout << "After 3 deletions  : "; 
	heap_1.levelorder_traversal(); 
	heap_1.print_tree(); 

	/* Height of tree. */
	cout << "Height             : " 
		 << heap_1.height() << endl; 


	return 0; 
}

/*******************************************************************/

