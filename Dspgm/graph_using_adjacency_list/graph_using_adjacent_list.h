#ifndef _GRAPH_USING_AL_
#define _GRAPH_USING_AL_

#include <iostream> 
#include <cstdlib>
#include <set>
#include <algorithm>
#include <utility>
#include <map>
#include <string> 
#include <fstream>
#include <cassert> 
#include <queue> 
#include <stack>
#include <sstream>
#include <list> 

using namespace std; 

/* Graph representation using Adjacenty List. */
class graph_using_AL{
public: 
	/* Public data types and constants. */
	enum _d_type{directed_graph, undirected_graph};	/* Directed and undirected graph.					*/
	enum _w_type{weighted_graph, unweighted_graph};	/* Weighted and unweighted graph.					*/

private: 
	/* Private data types. */
	enum color{white, gray, black};					/* Color to nodes. Used in BFS and DFS procedures.	*/
	
	/* Private data members. */
	string							 name		 ;	/* Name of the graph.								*/
	map<string, set<string> >		 data		 ;	/* To store the vertices/edges.						*/
	bool							 debug_flag	 ;	/* To set/unset debugging info.						*/
	_d_type							 d_type		 ;	/* Directed or undirected.							*/
	_w_type							 w_type		 ;	/* Weighted or unweighted graph.					*/
	
	/* For weighted graphs only. */
	map<pair<string, string>, int> edge_weights;	/* Weight of an edge.								*/		

public: 
	/* Constructor that takes a graph_name alone. 
	 * Creates a directed/unweighted graph by default. 
	 */
	graph_using_AL(string g_name) : 
	  name(g_name), debug_flag(false), d_type(directed_graph), w_type(unweighted_graph)
	{}

	/* Constructor that takes a graph_name and the type of graph (directed/undirecfed). 
	 * The graph is unweighted by default. 
	 */
	graph_using_AL(string g_name, _d_type type) : 
	  name(g_name), debug_flag(false), d_type(type), w_type(unweighted_graph)
	{}
	
	/* Constructor that takes a graph_name, directed/undirected type and 
	 * weighted/unweighted type. 
	 */
	graph_using_AL(string g_name, _d_type direction_type, _w_type weight_type) : 
	  name(g_name), debug_flag(false), d_type(direction_type), w_type(weight_type)
	{}

	/* Constructor that takes a graph_name and 'dot' file name. 
	 * It creates a graph as represented in the dot graph description language. 
	 * Not Implemented in the program. 
	 */
	graph_using_AL(string g_name, string dot_file_name); 
	
	/* Set and unset debug flag. */
	void   set_debug_flag(){ debug_flag = true;  }
	void unset_debug_flag(){ debug_flag = false; }

	/* Inserting edge to graph. Weight set to 0 for the edge. */
	void insert_edge(string from_v, string to_v); 

	/* For inserting an edge to weighted graph. */
	void insert_edge(string from_v, string to_v, int w); 

	/* Set the weight for an edge. */
	void set_weight(string from_v, string to_v, int weight); 

	/* To get the weight of an edge. */
	int get_weight(string from_v, string to_v); 

	/* To print the graph on to an output stream. */
	void print(ostream& out = cout); 

	/* To print the graph into a file in 'dot' graph description language format. */
	void print_to_file(ofstream& fout); 

	/* BFS traversal from a specific start vertex.  
	 * The 'parent' and the 'distance' maps are populated by the funtion call. 
	 */
	void BFS_visit(map<string, string> &parent, map<string, int> &distance, string start_vertex); 

	/* DFS traversal from a specific start vertex. 
	 * The 'parent', 'discovery_time' and 'finish_time' maps are populated
	 * by the function calls. 
	 */
	void DFS_visit(
		map<string, string> &parent, map<string, int> &d_time, 
		map<string, int> &f_time, string start_vertex
	); 

	/* To clear the graph. */
	void clear(){ data.clear(); }

	/* To check if empty. */
	bool empty() const{ return data.empty(); }

	/* Finding vertices and edges. */
	map<string, set<string> >::iterator find_vertex(string v); 
	bool find_edge(string from_v, string to_v); 

	/* Print the BFS/DFS tree from a particular vertex. */
	void print_bfs_tree(string start_vertex, ofstream &fout); 
	void print_dfs_tree(string start_vertex, ofstream &fout); 

	/* Deleting vertices and edges. */
	void delete_vertex(string v); 
	void delete_edge(string from_v, string to_v); 

	/* To get the count of vertices and edges. */
	size_t vertex_count() const{ return data.size(); }
	size_t edge_count() const; 

	/* Checks whether the graph is connected. 
	 * For directed graphs, it returns false. 
	 */
	bool is_connected(); 

	/* To find the minimum spanning tree using Kruskal's algorithm. 
	 * The tree_edges will be populated by the MST edges. 
	 */
	void find_MST_using_Kruskal(vector<pair<string, string> > &mst_tree_edges); 
	void find_MST_using_Kruskal_2(vector<pair<string, string> > &mst_tree_edges); 

	/* To find the minimum spanning tree using Prim's algorithm. 
	 * The tree_edges will be populated by the MST edges. 
	 */
	void find_MST_using_Prim(); 

	/* To print the graph (in dot language) with certain edges in a specific color to a
	 * given file. 
	 */
	void print_tree_with_edges_colored(vector<pair<string, string> > edges_to_be_colored, string color, ofstream &fout); 

	/* To print the edges and the corresponding weights. */
	void print_weights(); 

};

#endif

