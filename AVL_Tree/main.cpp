/**************************** main.cpp ****************************/
#include "AVL_Tree.h"
#include <string> 

/**********************************************************************/
using namespace std; 

/**********************************************************************/
/* Program entry point. */
int main(){
	AVL_Tree avl; 
	string cmd; 
	int data; 
	bool temp_trees_flag = false; 

	
	//avl.insert(3), avl.insert(1), avl.insert(2), avl.insert(4), avl.insert(5);  
	//avl.set_debug_flag(); 
	//avl.insert(-1), avl.insert(-2); 
	//avl.print_tree(); 
	//avl.delete_node(2), avl.delete_node(3); 
	//avl.insert(-4), avl.insert(-5); 
	//avl.delete_node(1); 
	//avl.delete_node(4); 
	


	while(1){
		cin >> cmd; 
		     if(cmd == "insert"     ) cin >> data, avl.insert(data); 
		else if(cmd == "delete"     ) cin >> data, avl.delete_node(data); 
		else if(cmd == "debug_set"	) avl.set_debug_flag()  , cout << "DEBUG Mode ON" << endl; 
		else if(cmd == "debug_unset") avl.unset_debug_flag(), cout << "DEBUG Mode OFF" << endl; 
		else if(cmd == "print"      ) avl.print_tree(); 
		else if(cmd == "exit"       ) break; 
		else                        cerr << "Wrong command" << endl; 
	}
	

	return 0; 
}

/*********************************************************************/