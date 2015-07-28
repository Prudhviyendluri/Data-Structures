#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace std;

void print_v(vector<int> v){
	if(v.size() == 0){
		return;
	}

	for(size_t i = 0; i < v.size(); i++) cout << v[i] << " ";
	cout << endl;
}

void create_lists(
	vector<int> &in, vector<int> &pre,
	vector<int> &in_left, vector<int> &in_right,
	vector<int> &pre_left, vector<int> &pre_right,
	int root
){
	vector<int>::iterator pos, tmp, root_pos;
	pos = find(in.begin(), in.end(), root);
	assert(pos != in.end());
	for(tmp = in.begin(); tmp != pos; tmp++) in_left.push_back(*tmp);
	for(tmp = pos+1; tmp != in.end(); tmp++) in_right.push_back(*tmp);

	root_pos = find(pre.begin(), pre.end(), root);
	for(tmp = root_pos+1; tmp != pre.end(); tmp++){
		if(find(in_left.begin(), in_left.end(), *tmp) != in_left.end()){
			pre_left.push_back(*tmp);
		}
		else{
			break;
		}
	}

	for(; tmp != pre.end(); tmp++) pre_right.push_back(*tmp);

}

void _create_tree_from_inorder_and_preorder(
	vector<int> &in, vector<int> &pre, ostream& out
){
	vector<int> in_left , in_right ;
	vector<int> pre_left, pre_right;

	if((in.size() == 0) && (pre.size() == 0)){ return; }
	if(pre.size() != 0) out << pre[0] << ";\n";

	create_lists(in, pre, in_left, in_right, pre_left, pre_right, pre[0]);
	//print_v(in_left), print_v(in_right), print_v(pre_left), print_v(pre_right), cout << endl;

	/* Left. */
	if((in_left.size() != 0) && (pre_left.size() != 0)) out << pre[0] << " -- ";
	_create_tree_from_inorder_and_preorder(in_left, pre_left, out);

	/* Right. */
	if((in_right.size() != 0) && (pre_right.size() != 0)) out << pre[0] << " -- ";
	_create_tree_from_inorder_and_preorder(in_right, pre_right, out);

	return;
}

void create_tree_from_inorder_and_preorder(
	vector<int> &in, vector<int> &pre, ostream& out = cout
){
	out << "graph tree{\n";
	_create_tree_from_inorder_and_preorder(in, pre, out);
	out << "}\n";
}

int main(){
	//int in_order [] = {8, 3, 7, 4, 9, 14, 6, 1, 0, 2};
	//int pre_order[] = {4, 7, 8, 3, 6, 14, 9, 2, 1, 0};

	int in_order [] = {3, 2, 1, 6, 4};
	int pre_order[] = {1, 3, 2, 6, 4};

	vector<int> v_in(in_order, in_order+(sizeof(in_order)/(sizeof(int))));
	vector<int> v_pre(pre_order, pre_order+(sizeof(pre_order)/(sizeof(int))));

	/* Printing tree into dot description language. */
	ofstream out_file("tree.dot");
	create_tree_from_inorder_and_preorder(v_in, v_pre, out_file);

	return 0;
}

