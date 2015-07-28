#include <algorithm>
#include <iostream>
#include <vector>

using namespace std; 

void print_vector(vector<int>& h){
	for(size_t i = 0; i < h.size(); i++){
		cout << h[i] << " "; 
	}
	cout << endl; 
}

int main(){
	int int_array[] = {1, 4, 5, 6, 1, 7}; 
	size_t size = (sizeof(int_array) / sizeof(int)); 
	vector<int> heap(int_array, int_array + size); 

	/* Creating a max-heap from the vector. */
	cout << "Creating heap: "; 
	make_heap(heap.begin(), heap.end()); 
	print_vector(heap); 

	/* Printing the max element. */
	cout << "Max element: " << heap.front() << endl; 

	/* Inserting a new element. */
	heap.push_back(24); 
	push_heap(heap.begin(), heap.end()); 
	cout << "Heap formed after inserting 24: "; 
	print_vector(heap); 
	
	/* Removing an element. 
	 * The element with the highest value is moved
	 * from 'first' to 'last-1'. 
	 */
	pop_heap(heap.begin(), heap.end()); 
	cout << "Heap formed after popping one element: "; 
	print_vector(heap);

	/* Removing last element. */
	cout << "Removing last element: "; 
	heap.pop_back(); 
	print_vector(heap); 

	/* Sorting vector heapsort, in ascending order. 
	 * The set of elements looses its properties as a
	 * heap. 
	 */
	sort_heap(heap.begin(), heap.end()); 
	cout << "After sorting: "; 
	print_vector(heap); 

	/* Checking if the set of elements has the 
	 * heap property. 
	 */
	if(is_heap(heap.begin(), heap.end()))
		cout << "It is a heap. " << endl; 
	else
		cout << "Not a heap. " << endl; 

	/* Re-heapifying. */
	cout << "Re-heapifying: "; 
	make_heap(heap.begin(), heap.end()); 
	print_vector(heap); 
	if(is_heap(heap.begin(), heap.end()))
		cout << "It is a heap. " << endl; 
	else
		cout << "Not a heap. " << endl; 

	/* is_heap_until() function returns an iterator
	 * to the first element in the range [first, last) which
	 * is not a valid position if the range is considered a 
	 * heap. If the entire range is a heap, the function returns
	 * last. */
	sort(heap.begin(), heap.end()); 
	reverse(heap.begin(), heap.end()); 
	reverse(heap.begin() + 2, heap.end()); 
	print_vector(heap); 
	vector<int>::iterator itr = is_heap_until(heap.begin(), heap.end()); 
	if(itr == heap.end()){
		cout << "The entire range is a heap" << endl; 
	}
	else{
		cout << "The first " << (itr - heap.begin()) 
			 << " elements form a heap" << endl; 
	}

	return 0; 
}
