/**************************** tree_int.h ****************************/
#ifndef __TREE_INT_H__
#define __TREE_INT_H__

#include "Node.h"
#include <iostream>

using std::ostream; 
using std::cout; 

/* A simple BST of integers. */

class Tree_Int{
private:
	Node<int> *root; 
	size_t tree_size; 
	static int deletion_flag; 

	/* Utility functions. */
	  

public: 
	Tree_Int():root(NULL), tree_size(0){}
	~Tree_Int(){ clear(); }

	/* Insert new item to tree. */
	void insert(int x); 

	/* To get the root of the tree. */
	Node<int>* get_root() const { return root; }

	/* Number of elements in the tree. */
	size_t size() const { return tree_size; }

	/* Check whether the tree is empty. */
	bool empty() const { return (tree_size == 0); }

	/* Traverse the tree. */
	void inorder   (Node<int> *node_ptr, ostream& out = cout) const ; 
	void preorder  (Node<int> *node_ptr, ostream& out = cout) const ; 
	void postorder (Node<int> *node_ptr, ostream& out = cout) const ; 
	void levelorder(Node<int> *node_ptr, ostream& out = cout) const ; 

	/* Traverse the tree; always from the root. */
	void inorder   (ostream& out = cout) const ; 
	void preorder  (ostream& out = cout) const ; 
	void postorder (ostream& out = cout) const ; 
	void levelorder(ostream& out = cout) const ; 

	/* Search for a key. */
	Node<int>* search(int key); 

	/* To delete a node with a specific value. */
	bool delete_node(int value); 
	bool delete_node(Node<int>* node); 

	/* Finding the parent of a node. */
	Node<int>* get_parent(Node<int>* node); 
	Node<int>* get_parent(int value); 

	/* Finding inorder successors. */
	Node<int>* get_inorder_successor(Node<int> *node);
	Node<int>* get_inorder_successor(int value);

	/* Finding inorder predecessor. */
	Node<int>* get_inorder_predecessor(Node<int> *node);
	Node<int>* get_inorder_predecessor(int value);

	/* To check whether a node is a left child or right child 
	 * of its parent. For root node, it returns false. 
	 */
	bool is_left_child (Node<int>* node); 
	bool is_right_child(Node<int>* node); 
	bool is_left_child (int value); 
	bool is_right_child(int value); 

	/* To check whether a given node is a root node. */
	bool is_root(Node<int>* node); 
	bool is_root(int value); 

	/* To check whether a given node is a leaf node. */
	bool is_leaf(Node<int>* node); 
	bool is_leaf(int value); 

	/* To check whether a node has only one child. */
	bool has_only_one_sibling(Node<int>* node); 
	bool has_only_one_sibling(int value); 

	/* To check whether a node has two children. */
	bool has_two_siblings(Node<int>* node); 
	bool has_two_siblings(int value); 

	/* Clear the tree. */
	void clear(); 
	void clear(Node<int>* node); 
};

#endif