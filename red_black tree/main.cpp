/**************************** main.cpp ****************************/
#include "Red_Black_Tree.h"
#include <string> 

/**********************************************************************/
using namespace std; 

/**********************************************************************/
/* Program entry point. */
int main(){
	Red_Black_Tree rbt; 
	string cmd; 
	int data; 
	bool temp_trees_flag = false; 
	init_color_mode();
	/*
	rbt.set_debug_flag(); 
	rbt.insert(10), rbt.insert(20), rbt.insert(-20), rbt.insert(-30), rbt.insert(-10); 
	rbt.insert(-5), rbt.insert(-8); 
	rbt.insert(90), rbt.print_tree(); 
	rbt.insert(100), rbt.print_tree(); */
	
	/*rbt.delete_node(10); rbt.delete_node(20); rbt.delete_node(-5); rbt.delete_node(90); 
	rbt.delete_node(-8);*/ 

	while(1){
		cin >> cmd; 
		     if(cmd == "insert"     ) cin >> data, rbt.insert(data); 
		else if(cmd == "delete"     ) cin >> data, rbt.delete_node(data); 
		else if(cmd == "debug_set"	) rbt.set_debug_flag()  , cout << "DEBUG Mode ON"  << endl; 
		else if(cmd == "debug_unset") rbt.unset_debug_flag(), cout << "DEBUG Mode OFF" << endl; 
		else if(cmd == "search"     ) cin >> data, cout << (rbt.search(data) ? "" : "Not ") << "Found" << endl; 
		else if(cmd == "clear"      ) rbt.clear(), rbt.print_tree(); 
		else if(cmd == "print"      ) rbt.print_tree(); 
		else if(cmd == "exit"       ) break; 
		else                        cerr << "Wrong command" << endl; 
	}
	
	return 0; 
}

/*********************************************************************/