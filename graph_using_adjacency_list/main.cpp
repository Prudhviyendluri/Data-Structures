#include "graph_using_adjacent_list.h"

using namespace std; 

/* Program entry point. */
int main(){
	//graph_using_AL g_1("g_1"); 
	//graph_using_AL g_1("g_1", graph_using_AL::undirected_graph); 
	graph_using_AL g_1("g_1", graph_using_AL::undirected_graph, graph_using_AL::weighted_graph);
	string cmd, v1, v2;  
	string from_v, to_v; 
	bool temp_trees_flag = false; 
	string f_name = "out_file.dot"; 
	ofstream fout; 
	int edge_weight; 
	vector<pair<string, string> > mst_edges; 

	g_1.set_debug_flag(); 

	//g_1.insert("10", "20"), g_1.insert("20", "30"), g_1.insert("30", "40"); 
	//g_1.insert("40", "50"), g_1.insert("10", "40"), g_1.insert("10", "50"); 
	//g_1.insert("20", "50"), g_1.insert("50", "20"); 

	//g_1.insert_edge("u", "v", 40), g_1.insert_edge("v", "y", 10), g_1.insert_edge("y", "x"), g_1.insert_edge("x", "v"); 
	//g_1.insert_edge("u", "x", 30), g_1.insert_edge("w", "y"), g_1.insert_edge("w", "z"), g_1.insert_edge("z", "z"); 
	//g_1.insert_edge("y", "w", 20), g_1.insert_edge("u", "w", 10); 
	
	g_1.insert_edge("a", "b", 7), g_1.insert_edge("a", "d", 5), g_1.insert_edge("b", "d", 9), g_1.insert_edge("d", "f", 6); 
	g_1.insert_edge("d", "e", 15), g_1.insert_edge("b", "e", 7), g_1.insert_edge("f", "e", 8), g_1.insert_edge("b", "c", 8); 
	g_1.insert_edge("e", "c", 5), g_1.insert_edge("e", "g", 9), g_1.insert_edge("f", "g", 11); 

	//g_1.insert_edge("1", "2", 4), g_1.insert_edge("1", "3", 1), g_1.insert_edge("2", "3", 2), g_1.insert_edge("2", "5", 2); 
	//g_1.insert_edge("3", "5", 3), g_1.insert_edge("3", "4", 4), g_1.insert_edge("4", "5", 3), g_1.insert_edge("4", "6", 6); 
	//g_1.insert_edge("6", "5", 3), g_1.insert_edge("5", "7", 4), g_1.insert_edge("6", "7", 5); 

	/*g_1.insert_edge("a", "b", 6), g_1.insert_edge("a", "g", 3 ), g_1.insert_edge("g", "h", 2 ), g_1.insert_edge("h", "b", 2); 
	g_1.insert_edge("g", "b", 4), g_1.insert_edge("f", "a", 9 ), g_1.insert_edge("f", "g", 9 ), g_1.insert_edge("f", "i", 8); 
	g_1.insert_edge("g", "i", 9), g_1.insert_edge("h", "i", 8 ), g_1.insert_edge("b", "c", 9 ), g_1.insert_edge("h", "c", 9); 
	g_1.insert_edge("h", "i", 8), g_1.insert_edge("i", "c", 7 ), g_1.insert_edge("c", "d", 4 ), g_1.insert_edge("c", "j", 5); 
	g_1.insert_edge("i", "j", 9), g_1.insert_edge("e", "i", 10), g_1.insert_edge("f", "e", 18), g_1.insert_edge("d", "j", 1); 
	g_1.insert_edge("j", "e", 3), g_1.insert_edge("d", "e", 4 ), g_1.insert_edge("c", "j", 5 ); */

	
	while(1){
		cout << ">> "; 
		cin >> cmd; 

		     if(cmd == "insert_e"    ) cin >> from_v >> to_v, g_1.insert_edge(from_v, to_v); 
		else if(cmd == "insert_ew"   ) cin >> from_v >> to_v >> edge_weight, g_1.insert_edge(from_v, to_v, edge_weight); 
		else if(cmd == "delete_v"    ) cin >> v1      , g_1.delete_vertex(v1    ); 
		else if(cmd == "delete_e"    ) cin >> v1 >> v2, g_1.delete_edge  (v1, v2); 
		else if(cmd == "debug_set"	 ) g_1.set_debug_flag()  , cout << "DEBUG Mode ON"  << endl; 
		else if(cmd == "debug_unset" ) g_1.unset_debug_flag(), cout << "DEBUG Mode OFF" << endl; 
		else if(cmd == "clear"       ) g_1.clear();  
		else if(cmd == "count_e"     ) cout << g_1.edge_count  () << endl; 
		else if(cmd == "count_v"     ) cout << g_1.vertex_count() << endl; 
		else if(cmd == "print"       ) g_1.print(); 
		else if(cmd == "print_file"  ) fout.open(f_name), assert(fout), g_1.print_to_file(fout), fout.close(); 
		else if(cmd == "print_bfs"	 ){
			cin >> from_v; fout.open(f_name), assert(fout); 
			g_1.print_bfs_tree(from_v, fout), fout.close(); 
		}
		else if(cmd == "print_dfs"	 ){
			cin >> from_v; fout.open(f_name), assert(fout); 
			g_1.print_dfs_tree(from_v, fout), fout.close(); 
		}
		else if(cmd == "is_connected") cout << (g_1.is_connected() ? "" : "Not ") << "Connected" << endl; 
		else if(cmd == "set_weight"  ) cin >> v1 >> v2 >> edge_weight, g_1.set_weight(v1, v2, edge_weight); 
		else if(cmd == "print_w"     ) g_1.print_weights(); 
		else if(cmd == "mst_kruskal" ){
			g_1.find_MST_using_Kruskal_2(mst_edges); 
			
			/* Print the MST onto file with the MST tree colored in blue. */
			fout.open(f_name), assert(fout), g_1.print_tree_with_edges_colored(mst_edges, "blue", fout), fout.close(); 
		}
		else if(cmd == "exit"        ) break; 
		else                          cerr << "Wrong command" << endl; 
	}

	return 0; 
}

