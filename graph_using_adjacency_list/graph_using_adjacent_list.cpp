#include "graph_using_adjacent_list.h" 

/* To insert an edge to the graph. */
void graph_using_AL::insert_edge(string from_v, string to_v){
	map<string, set<string> >::iterator from_temp_itr, to_temp_itr; 

	from_temp_itr = data.find(from_v); 
	to_temp_itr   = data.find(to_v  ); 

	if(from_temp_itr == data.end()){
		if(debug_flag) clog << "From_node " << from_v << " not found" << endl; 
		
		/* Inserting. */
		if(debug_flag) clog << "Inserting edge " << from_v << "-->" << to_v << endl; 
		set<string> temp_set; 
		temp_set.insert(to_v); 
		pair<string, set<string> > temp_pair(from_v, temp_set); 
		data.insert(temp_pair); 

		if(d_type == undirected_graph){
			if(to_temp_itr == data.end()){
				if(debug_flag) clog << "Inserting edge " << to_v << "-->" << from_v << endl; 
				temp_set.clear(); 
				temp_set.insert(from_v); 
				pair<string, set<string> > temp_pair(to_v, temp_set); 
				data.insert(temp_pair); 
			}
			else{
				to_temp_itr->second.insert(from_v); 
			}
		}
		else{
			/* It is a directed graph. */
			if(to_temp_itr == data.end()){
				if(debug_flag) clog << to_v << " is a new entry. " << endl; 
				set<string> temp_set_2; 
				pair<string, set<string> > temp_pair_2(to_v, temp_set_2); 
				data.insert(temp_pair_2); 
			}
		}
	}
	else{
		/* From node found. */
		if(debug_flag) clog << "From node "    << from_v << " found"    << endl; 
		if(debug_flag) clog << "Searching if " << to_v   << " is found in " << from_temp_itr->first << endl; 

		set<string>::iterator itr = find(from_temp_itr->second.begin(), from_temp_itr->second.end(), to_v); 

		if(itr == from_temp_itr->second.end()){
			if(debug_flag) clog << "To node " << to_v << " not found" << endl; 
			if(debug_flag) clog << "Creating the edge " << from_v << "-->" << to_v << endl; 
			from_temp_itr->second.insert(to_v); 

			if(d_type == undirected_graph){
				if(debug_flag) clog << "Creating the edge " << to_v << "-->" << from_v << endl; 
				from_temp_itr = data.find(to_v); 
				if(from_temp_itr == data.end()){
					if(debug_flag) clog << to_v << " is a new entry. " << endl; 
					set<string> temp_set; 
					temp_set.insert(from_v); 
					pair<string, set<string> > temp_pair(to_v, temp_set); 
					data.insert(temp_pair); 
				}
				else{
					if(from_v != to_v) from_temp_itr->second.insert(from_v); 
					else if(debug_flag) clog << "loop" << endl; 
				}
			}
		}
		else{
			if(debug_flag) clog << "The edge is already present" << endl;
		}
	}

	/* Setting the weight to 0 for weighted graphs. */
	if(w_type == weighted_graph){
		if(d_type == undirected_graph)
			set_weight(from_v, to_v, 0), set_weight(to_v, from_v, 0); 
		else
			set_weight(from_v, to_v, 0); 

	}
	if(debug_flag) print(); 

	return; 
}

/* For inserting an edge to weighted graph. */
void graph_using_AL::insert_edge(string from_v, string to_v, int w){
	/* If it is not a weighted graph, return. */
	if(w_type == unweighted_graph){
		if(debug_flag) clog << "It is an unweighted graph" << endl; 
		return; 
	}

	/* Insert the edge using the previous function. */
	insert_edge(from_v, to_v); 

	/* Set the weight. */
	if(d_type == undirected_graph) 
		set_weight(from_v, to_v, w), set_weight(to_v, from_v, w); 
	else 
		set_weight(from_v, to_v, w); 

	return; 
}


/* Set the weight for an edge. */
void graph_using_AL::set_weight(string from_v, string to_v, int w){
	/* If it is not a weighted graph, return. */
	if(w_type == unweighted_graph){
		if(debug_flag) clog << "Not a weighted graph" << endl; 
		return; 
	}

	/* If edge does not exits, then return. */
	if(find_edge(from_v, to_v) == false){
		if(debug_flag) clog << "Edge not found" << endl; 
		return; 
	}

	pair<string, string> temp_pair_1(from_v, to_v); 
	edge_weights[temp_pair_1] = w; 
	
	return; 
}

/* To get the weight of an edge. */
int graph_using_AL::get_weight(string from_v, string to_v){
	if(w_type == unweighted_graph) return -1; 
	else if(find_edge(from_v, to_v) == false) return -1; 
	else{
		pair<string, string> temp_pair_1(from_v, to_v); 
		return edge_weights.find(temp_pair_1)->second; 
	}
}

/* To print the graph. */
void graph_using_AL::print(ostream& out){
	if(empty()) out << "Empty" << endl; 

	map<string, set<string> >::const_iterator map_itr; 
	set<string>::const_iterator set_itr; 

	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		out << map_itr->first << ": "; 
		for(set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); set_itr ++){
			out << *set_itr; 

			/* If it is a weighted, print the weight too. */
			if(w_type == weighted_graph){
				pair<string, string> temp_pair_1(map_itr->first, *set_itr); 
				out << "(" << get_weight(map_itr->first, *set_itr) << ")"; 
			}

			out << " "; 
		}
		out << endl; 
	}
	
	return; 
}

/* To get the count of edges. */
size_t graph_using_AL::edge_count() const{
	map<string, set<string> >::const_iterator map_itr; 
	size_t size_counter = 0; 
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		/* Get the size of the set associated with current node. */
		size_counter += map_itr->second.size(); 
	}
	return (d_type == directed_graph) ? size_counter : (size_counter / 2); 
}

/* To print the graph into a file in 'dot' graph description language format. */
void graph_using_AL::print_to_file(ofstream& fout) {
	if(empty()) return; 
	assert(fout.good()); 
	string arrow      = ((d_type == directed_graph) ? " -> "    : " -- "   ); 
	string graph_type = ((d_type == directed_graph) ? "digraph " : "graph "); 

	map<string, set<string> >::const_iterator map_itr; 
	            set<string>  ::const_iterator set_itr; 
	
	fout << graph_type << name << "{" << endl;

	graph_using_AL g_temp = *this; 
	
	set<string> edges; 
	ostringstream oss; 
	for(map_itr = g_temp.data.begin(); map_itr != g_temp.data.end(); map_itr ++){
		if(map_itr->second.begin() == map_itr->second.end()){
			fout << "\t" << "\"" << map_itr->first << "\"" << ";\n"; 
		}
		else{
			for(set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); set_itr ++){
				fout << "\t" 
					 << "\"" << map_itr->first  << "\"" 
					 << arrow 
					 << "\"" << *set_itr        << "\""; 
				
				/* For weighted graph, print the individual edge weights. */
				if (w_type == weighted_graph){
					fout << "[label=" << get_weight(map_itr->first, *set_itr) << "]"; 
				}

				fout << "; \n"; 

				/* Delete the corresponding reverse-edge in the undirected graph. */
				if((d_type == undirected_graph) && (map_itr->first != *set_itr)){
					set<string>::iterator itr_temp = g_temp.data.find(*set_itr)->second.find(map_itr->first); 
					g_temp.data.find(*set_itr)->second.erase(itr_temp); 
				}
			}
		}
	}
	
	fout << "}" << endl; 

	return; 
}

/* Finding vertex. 
 * If not found, returns data.end() iterator. 
 */
map<string, set<string> >::iterator graph_using_AL::find_vertex(string v){
	return data.find(v); 
}

/* Finding edge. */
bool graph_using_AL::find_edge(string from_v, string to_v){
	map<string, set<string> >::iterator map_itr = find_vertex(from_v); 
	if(map_itr == data.end()) return false; 
	return (map_itr->second.find(to_v) != map_itr->second.end()); 
}

/* Deleting vertex. */
void graph_using_AL::delete_vertex(string v){
	/* Make sure the vertex is valid. */
	map<string, set<string> >::iterator map_itr = find_vertex(v); 
	if(map_itr == data.end()) return; 

	/* Deleting the weights. */
	map<pair<string, string>, int>::iterator w_itr; 
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); ){
		if((w_itr->first.first == v) || (w_itr->first.second == v)){
			edge_weights.erase(w_itr), w_itr = edge_weights.begin(); 
			continue; 
		}
		w_itr++; 
	}

	/* Deleting the vertex and the edges originating from the vertex. */
	data.erase(map_itr); 

	/* Delete the edges to this vertex. 
	 * Scanning the entire list is the only option. 
	 */
	set<string>::const_iterator set_itr; 
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		for(set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); set_itr ++){
			 if(*set_itr == v){
				 map_itr->second.erase(set_itr);
				 break; 
			 }
		}
	}

	return; 
}

/* Deleting edge. */
void graph_using_AL::delete_edge(string from_v, string to_v){
	map<string, set<string> >::iterator map_itr = find_vertex(from_v); 
	if(map_itr == data.end()) return; 
	
	/* Deleting the weights. */
	map<pair<string, string>, int>::iterator w_itr; 
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); ){
		if(d_type == directed_graph){
			if((w_itr->first.first == from_v) && (w_itr->first.second == to_v)){
				edge_weights.erase(w_itr), w_itr = edge_weights.begin(); 
				continue; 
			}
		}
		else if(d_type == undirected_graph){
			if(((w_itr->first.first == from_v) && (w_itr->first.second == to_v)) || 
				((w_itr->first.first == to_v) && (w_itr->first.second == from_v))
			){
				edge_weights.erase(w_itr), w_itr = edge_weights.begin(); 
				continue; 
			}
		}
		w_itr++; 
	}

	set<string>::iterator set_itr = map_itr->second.find(to_v); 
	if(set_itr == map_itr->second.end()) return; 
	map_itr->second.erase(set_itr); 

	/* If it is not a directed graph, an extra deletion needs to be done. */
	if((d_type == undirected_graph) && (from_v != to_v)){
		map_itr = find_vertex(to_v); 
		assert(map_itr != data.end()); 
		set_itr = map_itr->second.find(from_v); 
		map_itr->second.erase(set_itr); 
	}
	
	return; 
}

/* BFS traversal algorithm. 
 * The 'parent' and the 'distance' maps are populated by the funtion call. 
 */
void graph_using_AL::BFS_visit(map<string, string> &parent, map<string, int> &distance, string start_vertex){
	map<string, set<string> >::iterator map_itr; 
	queue<string> q; 

	/* Color each vertex as white. Initialize the distance and parent maps. */
	map<string, color> v_color; 
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		v_color .insert(pair<string,  color>(map_itr->first, white)); 
		distance.insert(pair<string,    int>(map_itr->first, -1   )); 
		parent  .insert(pair<string, string>(map_itr->first, ""   )); 
	}

	/* Make the start vertex gray. */
	v_color[start_vertex] = gray; 

	/* Set the distance and parent for the start vertex. */
	distance[start_vertex] = 0; 
	parent  [start_vertex] = ""; 

	/* Enqueue start_vertex. */
	q.push(start_vertex); 

	/* Starting the traversal of nodes. */
	string u, v; 
	while(! q.empty()){
		u = q.front(); 

		/* Get the adjacent nodes of the current node 'u'. */
		set<string> adj_nodes = data[u]; 

		/* For each adjacent nodes of the current node 'u'. */
		for(set<string>::iterator v = adj_nodes.begin(); v != adj_nodes.end(); v++){
			/* If the color of nodes is white, then process it. 
			 * If the color of node is black or gray, leave it. 
			 */
			if(v_color[*v] == white){
				/* This node has not been reached before. 
				 * So color it as gray. 
				 */
				v_color[*v] = gray; 

				/* Set the distance of this node based on the
				 * distance of the parent. 
				 */
				distance[*v] = distance[u] + 1; 

				/* Set the parent of v as u. */
				parent[*v] = u; 

				/* Insert this adjancent node in to queue
				 * to be processed later. 
				 */
				q.push(*v); 
			}
		}

		/* Dequeue the front element and color this node as black. */
		q.pop(); 
		v_color[u] = black; 
	}
}

/* Print the BFS tree from a particular vertex. */
void graph_using_AL::print_bfs_tree(string start_vertex, ofstream& fout){
	/* Check if 'fout' is good. */
	assert(fout.good()); 

	/* Find the start vertex. */
	map<string, set<string> >::iterator v_itr = find_vertex(start_vertex); 
	if(v_itr == data.end()){
		/* Vertex not found. */
		cerr << "Start Vertex not found." << endl; 
		return; 
	}

	map<string, string>  parent  ; 
	map<string,    int>  distance; 

	/* Do the BFS traversal. 
	 * The 'parent' and the 'distance' containers will be populated by this function. 
	 */
	BFS_visit(parent, distance, start_vertex); 

	/* Printing the parent details. */
	if(debug_flag) clog << "Parent array: " << endl; 
	vector<pair<string, string> > vp; 
	for(map<string, string>::iterator p_itr = parent.begin(); p_itr != parent.end(); p_itr++){
		vp.push_back(pair<string, string>(p_itr->first, p_itr->second)); 
		if(debug_flag) cout << p_itr->first << " <-- " << p_itr->second << endl; 
	}

	print_tree_with_edges_colored(vp, "red", fout); 

	return; 
}

/* To print the graph, with certain edges in a specific color. */
void graph_using_AL::print_tree_with_edges_colored(vector<pair<string, string> > edges_to_be_colored, string color, ofstream& fout){
	/* Make sure the file stream is opened. */
	assert(fout.good()); 
	
	vector<pair<string, string> > &edges = edges_to_be_colored; 

	/* Create a graph using the parent information. */
	map<string, set<string> >::iterator map_itr; 
	set<string>::const_iterator set_itr; 

	string graph_type = ((d_type == undirected_graph) ? "graph " : "digraph "); 
	string arrow      = ((d_type == undirected_graph) ? " -- "   : " -> "    ); 

	fout << graph_type << name << "{" << endl; 
	graph_using_AL g_temp = *this; 

	for(vector<pair<string, string> >::iterator p_itr = edges.begin(); p_itr != edges.end(); p_itr ++){
		
		/* When printing BFS tree, the the parent of root is empty. */
		if(p_itr->second.begin() == p_itr->second.end()) continue; 

		fout << "\t\"" << p_itr->second  << "\"" << arrow << "\"" << p_itr->first; 
		fout << "\" [color=" << color; 
		if(w_type == weighted_graph){
			/* It is a weighted graph. So print the weight too (as the label of the edge 
			 * along with the color. 
			 */
			fout << " label = " << edge_weights.find(pair<string, string>(p_itr->second, p_itr->first))->second; 
		}
		fout << "];\n"; 

		/* Delete the corresponding reverse-edge in the undirected graph. */
		if((d_type == undirected_graph) && (p_itr->second != p_itr->first)){
			set<string>::iterator itr_temp = g_temp.data.find(p_itr->first)->second.find(p_itr->second); 
			if(debug_flag) clog << "Deleting " << p_itr->first << " --> " << p_itr->second << endl; 
			g_temp.data.find(p_itr->first)->second.erase(itr_temp); 
		}
	}

	if(debug_flag) g_temp.print(); 

	for(vector<pair<string, string> >::iterator p_itr = edges.begin(); p_itr != edges.end(); p_itr++){
		if(p_itr->second.begin() == p_itr->second.end()) continue; 
		if(p_itr->second != p_itr->first){
			if(debug_flag) clog << "Deleting " << p_itr->second << " --> " << p_itr->first << endl; 
			set<string>::iterator itr_temp = g_temp.data.find(p_itr->second)->second.find(p_itr->first); 
			g_temp.data.find(p_itr->second)->second.erase(itr_temp); 
		}
	}

	if(debug_flag) g_temp.print(); 

	for(map_itr = g_temp.data.begin(); map_itr != g_temp.data.end(); map_itr ++){
		if(map_itr->second.begin() == map_itr->second.end()){
			fout << "\t" << "\"" << map_itr->first << "\"" << ";\n"; 
		}
		else{
			for(set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); set_itr ++){
				fout << "\t\"" 
					 << map_itr->first  << "\"" 
					 << arrow  
					 << "\"" << *set_itr << "\""; 
									
				if(w_type == weighted_graph){
					/* It is a weighted graph. So print the weight too (as the label of the edge along with the color.	  */
					fout << "[label = " << edge_weights.find(pair<string, string>(map_itr->first, *set_itr))->second
					     << "]"; 
				}

				fout << "\n";  

				if((map_itr->first != *set_itr) && (d_type == undirected_graph)){
					if(debug_flag) clog << "Deleting " << *set_itr << " --> " << map_itr->first << endl; 
					set<string>::iterator itr_temp = g_temp.data.find(*set_itr)->second.find(map_itr->first); 
					g_temp.data.find(*set_itr)->second.erase(itr_temp); 
				}
			}
		}
	}
	fout << "}" << endl; 

	return; 
}
	
/* DFS traversal from a specific start vertex. 
 * The 'parent', 'discovery_time' and 'finish_time' maps are populated
 * by the function calls. 
 */
void graph_using_AL::DFS_visit(
	map<string, string> &parent, map<string, int> &d_time, 
	map<string, int> &f_time, string start_vertex
){
	map<string, set<string> >::iterator map_itr; 
	stack<string> stk; 

	/* Color each vertex as white. 
	 * Initialize the parent, d_time (discovery time) and f_time (finish
	 * time) containers. 
	 */
	map<string, color> v_color; 
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		v_color .insert(pair<string,  color>(map_itr->first, white)); 
		d_time.insert(pair<string,    int>(map_itr->first, -1   )); 
		f_time.insert(pair<string,    int>(map_itr->first, -1   )); 
		parent  .insert(pair<string, string>(map_itr->first, ""   )); 
	}

	/* Initialize 'time' to 0. */
	size_t time = 0; 

	/* Push start_vertex on stack. */
	stk.push(start_vertex); 
	d_time[start_vertex] = ++time; 
	v_color[start_vertex] = gray; 
	
	/* To save the remaining vertices to be checked from one vertex. */
	map<string, set<string>::iterator> state; 
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		state[map_itr->first] = map_itr->second.begin(); 
	}

	/* Starting the traversal of nodes. */
	string u, v; 
	while(! stk.empty()){
		/* Get the top vertex from the stack. */
		u = stk.top(); 
		//cout << "u: " << u << endl; 
		if(state[u] != data[u].end()){
			v = *state[u]++;
			//cout << "v: " << v << endl; 
		}
		else{
			v_color[u] = black; 
			f_time[u]  = ++time; 
			//cout << "Popping " << stk.top() << endl; 
			stk.pop(); 
			continue; 
		}

		if(v_color[v] == white){
			v_color[v] = gray; 
			stk.push(v); 
			parent[v] = u; 
			d_time[v] = ++time; 
		}
	}

	return; 
}

/* Print the BFS tree from a particular vertex. */
void graph_using_AL::print_dfs_tree(string start_vertex, ofstream& fout){
	/* Check if 'fout' is good. */
	assert(fout.good()); 

	/* Find the start vertex. */
	map<string, set<string> >::iterator v_itr = find_vertex(start_vertex); 
	if(v_itr == data.end()){
		/* Vertex not found. */
		cerr << "Start vertex not found." << endl; 
		return; 
	}

	map<string, string>  parent;  /* Parent of node.		  */
	map<string,    int>  d_time;  /* Discovery time of node.  */
	map<string,    int>  f_time;  /* Finish time of node.     */
	
	char                 c_temp[100]; 

	/* Do the DFS traversal. */
	DFS_visit(parent, d_time, f_time, start_vertex); 

	map<string, set<string> >::iterator map_itr; 
	set<string>::const_iterator set_itr; 

	string graph_type = ((d_type == undirected_graph) ? "graph " : "digraph "); 
	string arrow      = ((d_type == undirected_graph) ? " -- "   : " -> "   ); 

	map<string, string> d_time_string; 
	map<string, string> f_time_string; 

	for(map<string, int>::iterator d_itr = d_time.begin(); d_itr != d_time.end(); d_itr++){
		_itoa_s(d_itr->second, c_temp, 10); 
		d_time_string.insert(pair<string, string>(d_itr->first,string(c_temp))); 
	}

	for(map<string, int>::iterator f_itr = f_time.begin(); f_itr != f_time.end(); f_itr++){
		_itoa_s(f_itr->second, c_temp, 10); 
		f_time_string.insert(pair<string, string>(f_itr->first, string(c_temp))); 
	}

	fout << graph_type << name << "{" << endl; 
	graph_using_AL g_temp = *this; 

	for(map<string, string>::iterator p_itr = parent.begin(); p_itr != parent.end(); p_itr++){
		if(p_itr->second.begin() == p_itr->second.end()) continue; 
		fout << "\t\"" << p_itr->second  << "(" << d_time_string[p_itr->second] 
					 << ", " << f_time_string[p_itr->second] << ")" << "\"" 
					 << arrow  
					 << "\"" << p_itr->first << "(" << d_time_string[p_itr->first] 
					 << ", " << f_time_string[p_itr->first] << ")"; 
		fout << "\" [color=red "; 
		if(w_type == weighted_graph){
			/* It is a weighted graph. So print the weight too (as the label of the edge 
			 * along with the color. 
			 */
			fout << " label = " << edge_weights.find(pair<string, string>(p_itr->second, p_itr->first))->second; 
		}


		fout << "];\n"; 

		/* Delete the corresponding reverse-edge in the undirected graph. */
		if((d_type == undirected_graph) && (p_itr->second != p_itr->first)){
			set<string>::iterator itr_temp = g_temp.data.find(p_itr->first)->second.find(p_itr->second); 
			if(debug_flag) clog << "Deleting " << p_itr->first << " --> " << p_itr->second << endl; 
			g_temp.data.find(p_itr->first)->second.erase(itr_temp); 
		}
	}

	if(debug_flag) g_temp.print(); 

	for(map<string, string>::iterator p_itr = parent.begin(); p_itr != parent.end(); p_itr++){
		if(p_itr->second.begin() == p_itr->second.end()) continue; 
		if(p_itr->second != p_itr->first){
			if(debug_flag) clog << "Deleting " << p_itr->second << " --> " << p_itr->first << endl; 
			set<string>::iterator itr_temp = g_temp.data.find(p_itr->second)->second.find(p_itr->first); 
			g_temp.data.find(p_itr->second)->second.erase(itr_temp); 
		}
	}

	if(debug_flag) g_temp.print(); 

	for(map_itr = g_temp.data.begin(); map_itr != g_temp.data.end(); map_itr ++){
		if(map_itr->second.begin() == map_itr->second.end()){
			fout << "\t\"" << map_itr->first  << "(" << d_time_string[map_itr->first] 
				 << ", " << f_time_string[map_itr->first] << ")" << "\"" << ";\n"; 
		}
		else{
			for(set_itr = map_itr->second.begin(); set_itr != map_itr->second.end(); set_itr ++){
				fout << "\t\"" << map_itr->first  << "(" << d_time_string[map_itr->first] 
					 << ", " << f_time_string[map_itr->first] << ")" << "\"" 
					 << arrow  
					 << "\"" << *set_itr << "(" << d_time_string[*set_itr] 
					 << ", " << f_time_string[*set_itr] << ")\" "; 
	
				if(w_type == weighted_graph){
					/* It is a weighted graph. So print the weight too (as the label of the edge along with the color.	  */
					fout << "[label = " << edge_weights.find(pair<string, string>(map_itr->first, *set_itr))->second
					     << "]"; 
				}
				fout << endl; 
				
				if((map_itr->first != *set_itr) && (d_type == undirected_graph)){
					if(debug_flag) clog << "Deleting " << *set_itr << " --> " << map_itr->first << endl; 
					set<string>::iterator itr_temp = g_temp.data.find(*set_itr)->second.find(map_itr->first); 
					g_temp.data.find(*set_itr)->second.erase(itr_temp); 
				}
			}
		}
	}
	fout << "}" << endl; 

	return; 
}

/* Checks whether the graph is connected. 
 * For directed graphs, it returns false. 
 * Complexity: O(|V| + |E|); since it uses BFS algorithm. 
 */
bool graph_using_AL::is_connected(){
	/* Return false if the graph is a directed graph. */
	if(d_type == directed_graph) return false; 

	map<string, string>  parent  ; 
	map<string,    int>  distance; 

	/* Let us start from any arbitrary vertex. */
	string start_vertex = data.begin()->first; 

	/* Construct the BFS tree. 
	 * If it contains all the vertices of the graph, then the graph is connected. 
	 * Complexity: O(|V| + |E|). 
	 */
	BFS_visit(parent, distance, start_vertex); 

	/* Check how many nodes have non-null parents. */
	int temp_counter = 0; 
	for(map<string, string>::iterator p_itr = parent.begin(); p_itr != parent.end(); p_itr++){
		if(debug_flag) cout << p_itr->first << " <-- " << p_itr->second << endl; 
		if(p_itr->second != ""){
			temp_counter ++; 
		}
	}

	if(debug_flag) cout << "temp_counter: " << temp_counter << endl; 

	/* '+1' because, for the start vertex, the parent will be Null/Empty. */
	return ((temp_counter + 1) == vertex_count()); 
}

/* To print the edges and the corresponding weights. */
void graph_using_AL::print_weights(){
	map<pair<string, string>, int>::iterator w_itr; 
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); w_itr++){
		cout << w_itr->first.first << " -> " << w_itr->first.second << ": " << w_itr->second << endl; 
	}
	
	return; 
}

/* To find the minimum spanning tree using Kruskal's algorithm. 
 * The mst_tree_edges will be populated by the MST edges. 
 */
void graph_using_AL::find_MST_using_Kruskal(vector<pair<string, string> > &mst_tree_edges){
	list<set<string> >					forest		; 
	set<string>							temp_set	; 
	map<string, set<string> >::iterator map_itr		; 

	/* Populate forest. Each vertex is separte tree. */
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		temp_set.insert(map_itr->first); 
		forest.push_back(temp_set); 
		temp_set.clear(); 
	}
	
	/* Sorting based on weight. 
	 * Create a map with weight as the key and the edge as the value. 
	 */
	multimap<int, pair<string, string> >					temp_edge_weights	; 
	map<pair<string, string>, int>::iterator				w_itr				; 
	typedef multimap<int, pair<string, string> >::iterator	mm_itr				; 

	/* For each edge in the graph. */
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); w_itr++){
		if(d_type == undirected_graph){
			/* Find the list of edges with this weight. */
			pair<mm_itr, mm_itr> mm_itr_pair = temp_edge_weights.equal_range(w_itr->second); 

			/* Make sure the find is successful. */
			if(mm_itr_pair.first != mm_itr_pair.second){
				if(debug_flag) cout << "Weight found: " << w_itr->second << endl;

				/* Traverse each edge with this weight. */
				bool found_flag = false; 
				for(mm_itr mm_itr_1 = mm_itr_pair.first; mm_itr_1 != mm_itr_pair.second; mm_itr_1 ++){
					if(debug_flag) cout << "Comparing: " << mm_itr_1->second.first  << ", " << w_itr->first.second << endl; 
					if(debug_flag) cout << "Comparing: " << mm_itr_1->second.second << ", " << w_itr->first.first  << endl; 

					if((mm_itr_1->second.first == w_itr->first.second) && (mm_itr_1->second.second == w_itr->first.first)){
						found_flag = true; 
						break; 
					}
				}
				
				/* Check if found. */
				if(found_flag == false){
					/* None of the edge matched. */
					if(debug_flag) cout << "inserting " << w_itr->second << ", " << w_itr->first.first << ", " 
										<< w_itr->first.second << endl; 
					temp_edge_weights.insert(pair<int, pair<string, string> >(w_itr->second, w_itr->first)); 
				}
				else{
					/* One of the edge matched. */
					if(debug_flag) cout << "Edge " << w_itr->first.first << ", " << w_itr->first.second 
										<< " need not be inserted" << endl; 
				}
			}
			else{
				/* Find is unsuccessful. */
				if(debug_flag) cout << "Weight not found: " << w_itr->second << endl;
				if(debug_flag) cout << "inserting " << w_itr->second << ", " << w_itr->first.first << ", " 
													<< w_itr->first.second << endl; 

				/* Insert the new edge. */
				temp_edge_weights.insert(pair<int, pair<string, string> >(w_itr->second, w_itr->first)); 
			}
		}
		else{
			/* Directed graph; so insert both pair of edges. */
			temp_edge_weights.insert(pair<int, pair<string, string> >(w_itr->second, w_itr->first)); 
		}
	}
	
	/* Printing the sorted list. */
	multimap<int, pair<string, string> >::iterator w_temp_itr; 
	if(debug_flag){
		cout << "Sorted list of edges: " << endl; 
		for(w_temp_itr = temp_edge_weights.begin(); w_temp_itr != temp_edge_weights.end(); w_temp_itr ++){
			cout << w_temp_itr->second.first << "->" << w_temp_itr->second.second << ": " << w_temp_itr->first << endl; 
		}
	}

	/* Printing forest. */
	if(debug_flag){
		cout << "Current forest: " << endl; 
		for(list<set<string> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
			if(! f_itr->empty()){
				cout << "{"; 
				for(set<string>::iterator set_string_itr = f_itr->begin(); set_string_itr != f_itr->end(); set_string_itr ++){
					cout << *set_string_itr << " "; 
				}
				cout << "} " << endl; 
			}
		}
	}

	/* For each edge in increasing order of weight. */
	for(w_temp_itr = temp_edge_weights.begin(); w_temp_itr != temp_edge_weights.end(); w_temp_itr ++){
		if(debug_flag){
			cout << "Testing edge " << w_temp_itr->second.first << " -> " << w_temp_itr->second.second; 
			cout << " (" << w_temp_itr->first << ")" << endl; 
		}

		if(debug_flag) cout << "Checking whether in same set: " 
							<< w_temp_itr->second.first << ", " << w_temp_itr->second.second << endl; 
		list<set<string> >::iterator itr_1, itr_2; 
		     set<string>  ::iterator itr_3, itr_4; 
		bool found_flag = false; 

		/* Find the set of the first element. */
		found_flag = false; 
		for(itr_1 = forest.begin(); itr_1 != forest.end(); itr_1 ++){
			itr_3 = itr_1->find(w_temp_itr->second.first); 
			if(itr_3 != itr_1->end()){ found_flag = true; break; }
		}
		assert(found_flag == true); 

		/* Find the set of the second element. */
		for(itr_2 = forest.begin(); itr_2 != forest.end(); itr_2 ++){
			itr_4 = itr_2->find(w_temp_itr->second.second); 
			if(itr_4 != itr_2->end()){ found_flag = true; break; }
		}
		assert(found_flag == true); 

		
		/* See if they are in the same set or not. */
		if(itr_1 != itr_2){
			/* They are in different trees. */
			if(debug_flag) cout << "They are in different trees. " << endl; 

			/* Add them to the set of edges in the MST. */
			if(debug_flag) cout << "Adding the edges " << *itr_3 << ", " << *itr_4 << " to the MST. " << endl; 
			mst_tree_edges.push_back(pair<string, string>(*itr_3, *itr_4)); 

			/* Combine them into a single tree (set). */
			for(set<string>::iterator itr_5 = itr_2->begin(); itr_5 != itr_2->end(); itr_5++){
				itr_1->insert(*itr_5); 
			}
			itr_2->clear(); 
			
		}
		else{
			if(debug_flag) cout << "They are in the same tree. So cannot be added" << endl; 
		}

		if(debug_flag){
			for(vector<pair<string, string> >::iterator te_itr = mst_tree_edges.begin(); te_itr != mst_tree_edges.end(); te_itr ++){
				cout << te_itr->first << ", " << te_itr->second << endl; 
			}
		}

		/* If all the edges are added, you can stop. 
		 * For a graph with n vertices, its MST will contain (n-1) edges. 
		 */
		if(mst_tree_edges.size() == vertex_count() - 1){
			if(debug_flag) cout << "All the edges have been added. " << endl; 
			break; 
		}

		/* Printing forest. */
		if(debug_flag){
			cout << "Current forest: " << endl; 
			for(list<set<string> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
				if(! f_itr->empty()){
					cout << "{"; 
					for(set<string>::iterator set_string_itr = f_itr->begin(); set_string_itr != f_itr->end(); set_string_itr ++){
						cout << *set_string_itr << " "; 
					}
					cout << "} " << endl; 
				}
			}
		}
	}
	
	return; 
}

void graph_using_AL::find_MST_using_Kruskal_2(vector<pair<string, string> > &mst_tree_edges){
	set<set<string> >					forest		; 
	set<string>							temp_set	; 
	map<string, set<string> >::iterator map_itr		; 

	/* Populate forest. Each vertex is separate set. */
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		temp_set.insert(map_itr->first); 
		forest.insert(temp_set); 
		temp_set.clear(); 
	}
	
	/* Sorting based on weight. 
	 * Create a multi-map with weight as the key and the edge as the value. 
	 * There may be more than one edge with the same weight. So use multimap. 
	 */
	multimap<double, pair<string, string> >						temp_edge_weights	; 
	map<pair<string, string>, int>::iterator					w_itr				; 
	typedef multimap<int, pair<string, string> >::iterator	mm_itr				; 

	/* Creating map between weights and set of edges (with that weight). This map will be sorted by weights. */
	//cout << "Creating map between weights and set of edges" << endl; 
	map<double, set<pair<string, string> > > weight_sorted_edges; 
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); w_itr++){
		if(weight_sorted_edges[w_itr->second].find(pair<string, string>(w_itr->first.second, w_itr->first.first)) == weight_sorted_edges[w_itr->second].end()){
			pair<string, string> temp_p_ss(w_itr->first); 
			weight_sorted_edges[w_itr->second].insert(temp_p_ss); 
		}
	}

	/* Printing sorted list of weights. */
	if(1){
		for(map<double, set<pair<string, string> > >::iterator itr_1 = weight_sorted_edges.begin(); itr_1 != weight_sorted_edges.end(); itr_1++){
			cout << itr_1->first << " --> "; 
			for(set<pair<string, string> >::iterator itr_2 = itr_1->second.begin(); itr_2 != itr_1->second.end(); itr_2 ++){
				cout << "(" << itr_2->first << ", " << itr_2->second << ") "; 
			}
			cout << endl; 
		}
	}

	/* Printing forest. */
	if(1){
		cout << "Current forest: " << endl; 
		for(set<set<string> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
			if(! f_itr->empty()){
				cout << "{"; 
				for(set<string>::iterator set_string_itr = f_itr->begin(); set_string_itr != f_itr->end(); set_string_itr ++){
					cout << *set_string_itr << " "; 
				}
				cout << "} " << endl; 
			}
		}
	}

	/* For each edge ordered by weight. */
	for(map<double, set<pair<string, string> > >::iterator itr_1 = weight_sorted_edges.begin(); itr_1 != weight_sorted_edges.end(); itr_1++){
		for(set<pair<string, string> >::iterator itr_2 = itr_1->second.begin(); itr_2 != itr_1->second.end(); itr_2 ++){
			cout << "Comparing " << itr_2->first << ", " << itr_2->second << endl; 
			string e1 = itr_2->first, e2 = itr_2->second; 
			set<string>::iterator set_1_itr, set_2_itr; 

			/* Finding set_1. */
			set<set<string> >::iterator f_itr_1; 
			for(f_itr_1 = forest.begin(); f_itr_1 != forest.end(); f_itr_1 ++){
				set_1_itr = f_itr_1->find(e1); 
				if(set_1_itr != f_itr_1->end()) break; 
			}

			/* Finding set_2. */
			set<set<string> >::iterator f_itr_2; 
			for(f_itr_2 = forest.begin(); f_itr_2 != forest.end(); f_itr_2 ++){
				set_2_itr = f_itr_2->find(e2); 
				if(set_2_itr != f_itr_2->end()) break; 
			}

			/* Check if the sets are unequal. */
			if(f_itr_1 != f_itr_2){
				/* Combine them. */
				set<string> new_set; 
				for(set<string>::iterator temp_itr = f_itr_1->begin(); temp_itr != f_itr_1->end(); temp_itr++) new_set.insert(*temp_itr); 
				for(set<string>::iterator temp_itr = f_itr_2->begin(); temp_itr != f_itr_2->end(); temp_itr++) new_set.insert(*temp_itr); 
				
				forest.erase(f_itr_1); 
				forest.erase(f_itr_2); 
				forest.insert(new_set); 

				/* Adding this edge to the set of tree edges. */
				cout << "Inserting " << itr_2->first << ", " << itr_2->second << endl; 
				mst_tree_edges.push_back(*itr_2); 
				if(forest.size() == 1){
					cout << "Completed" << endl; 
					return; 
				}

				if(1){
					cout << "Current forest: " << endl; 
					for(set<set<string> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
						if(! f_itr->empty()){
							cout << "{"; 
							for(set<string>::iterator set_string_itr = f_itr->begin(); set_string_itr != f_itr->end(); set_string_itr ++){
								cout << *set_string_itr << " "; 
							}
							cout << "} " << endl; 
						}
					}
				}
			}
			else{
				cout << "Equal" << endl; 
			}
		}
	}
	return; 
}