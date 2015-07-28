/**************************** main.cpp ****************************/
#include "tree_int.h"
#include <iostream>
#include <array>

using namespace std; 

int main(){
	Tree_Int t; 
	array<int, 8> data = {4, 2, 1, 3, 6, 5, 7, 8}; 
	array<int, 8>::iterator itr; 
	Node<int>* node_ptr = NULL; 

	/* Populating BST. 
	 * You get a tree as follows: 
	 *                       4
	 *                      / \
	 *                     2   6
	 *                    / \ / \
	 *                   1  3 5  7
	 *                            \
	 *                             8
	 */
	for(itr = data.begin(); itr != data.end(); itr++){
		t.insert(*itr); 
	}
	
	/* Traversing the tree. */
	cout << "Inorder   : ", t.inorder   (), cout << endl;	/* Depth-first.   */
	cout << "Preorder  : ", t.preorder  (), cout << endl;	/* Depth-first.   */
	cout << "Postorder : ", t.postorder (), cout << endl;	/* Depth-first.   */
	cout << "Levelorder: ", t.levelorder(), cout << endl;	/* Breadth-first. */

	/* Searching the tree. */
	cout << "\nSearching tree for specific nodes: " << endl; 
	cout << "10: " << ((t.search(10) == NULL) ? "Not Found" : "Found") << endl; 
	cout << "4 : " << ((t.search(4 ) == NULL) ? "Not Found" : "Found") << endl; 
	cout << "7 : " << ((t.search(7 ) == NULL) ? "Not Found" : "Found") << endl; 
	cout << "11: " << ((t.search(11) == NULL) ? "Not Found" : "Found") << endl; 
	cout << endl; 

	/* Getting the inorder successor of a node. */
	array<int, 7> input_data = {6, 4, 1, 5, 3, 7, 9}; 
	for(array<int, 7>::iterator temp_itr = input_data.begin(); 
		temp_itr != input_data.end()				         ; 
		temp_itr++
	){
		cout << "Inorder successor of " << *temp_itr << ": "; 
		node_ptr = t.get_inorder_successor(*temp_itr); 
		if(node_ptr == NULL) cout << "NULL" << endl; 
		else cout << node_ptr->get_data() << endl; 
	}
	cout << endl; 

	/* Getting the inorder predecessor of a node. */
	for(array<int, 7>::iterator temp_itr = input_data.begin(); 
		temp_itr != input_data.end()				         ; 
		temp_itr++
	){
		cout << "Inorder predecessor of " << *temp_itr << ": "; 
		node_ptr = t.get_inorder_predecessor(*temp_itr); 
		if(node_ptr == NULL) cout << "NULL" << endl; 
		else cout << node_ptr->get_data() << endl; 
	}
	cout << endl; 

	/* Getting the parent node. */
	for(array<int, 7>::iterator temp_itr = input_data.begin(); 
		temp_itr != input_data.end()				         ; 
		temp_itr++
	){
		cout << "Parent of " << *temp_itr << ": "; 
		node_ptr = t.get_parent(*temp_itr); 
		if(node_ptr == NULL) cout << "NULL" << endl; 
		else cout << node_ptr->get_data() << endl; 
	}
	cout << endl; 

	/* Checking whether a node is a left child or right child. */
	for(array<int, 7>::iterator temp_itr = input_data.begin(); 
		temp_itr != input_data.end()				         ; 
		temp_itr++
	){
		cout << *temp_itr << ": "; 
		     if(t.is_left_child (*temp_itr)) cout << "Left child"  << endl; 
		else if(t.is_right_child(*temp_itr)) cout << "Right child" << endl; 
		else if(t.is_root       (*temp_itr)) cout << "Root Node"   << endl; 
		else                                 cout << "Not found"   << endl; 
	}

	/* Checking whether a node has one child or two children. */
	for(array<int, 7>::iterator temp_itr = input_data.begin(); 
		temp_itr != input_data.end()				         ; 
		temp_itr++
	){
		cout << *temp_itr << ": "; 
		if(t.has_only_one_sibling (*temp_itr)) cout << "has only one child"  << endl; 
		else if(t.has_two_siblings(*temp_itr)) cout << "has two children" << endl; 
		else if(t.is_leaf(*temp_itr)) cout << "It is a leaf node" << endl; 
		else cout << "Not found" << endl; 
	}
	cout << endl; 

	/* Deleting node 7 --> only right child. */
	cout << "Deleting 7: "; 
	t.delete_node(7); 
	t.inorder(), cout << ", "; 
	t.levelorder(), cout << endl; 

	/* Deleting node 4 --> root node and has two children. */
	cout << "Deleting 4: "; 
	t.delete_node(4); 
	t.inorder(), cout << ", "; 
	t.levelorder(), cout << endl; 

	/* Deleting node 5 --> root node and has two children. */
	cout << "Deleting 5: ";  
	t.delete_node(5); 
	t.inorder(), cout << ", "; 
	t.levelorder(), cout << endl; 

	/* Clear the right subtree of root. */
	cout << "\nClearing the right-subtree of root. " << endl; 
	t.clear(t.get_root()->get_right_ptr()); 
	cout << "Size of tree: " << t.size() << endl; 
	cout << "Inorder     : ", t.inorder(), cout << endl; 
	cout << "Levelorder  : ", t.levelorder(), cout << endl; 

	/* Clear the left-subtree of root. */
	cout << "\nClearing the left sub-tree of root. " << endl; 
	t.clear(t.get_root()->get_left_ptr()); 
	cout << "Size of tree: " << t.size() << endl; 
	cout << "Inorder     : ", t.inorder(), cout << endl; 
	cout << "Levelorder  : ", t.levelorder(), cout << endl; 

	/* Clearing the entire tree. */
	t.clear(); 
	
	return 0; 
}
