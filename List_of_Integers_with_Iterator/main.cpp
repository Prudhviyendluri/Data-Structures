#include "List_Int.h"
#include <list>

using namespace std; 

/* Program entry point. */
int main(){
	List_Int l1; 
	List_Int::iterator j = l1.end(); 

	l1.push_back(10); 
	l1.insert(l1.begin(), 20); 
	l1.push_back(30), l1.push_back(40); 
	cout << "Before: ", l1.print(); 

	j = l1.begin(); 
	j++, j++; 
	cout << *j << endl; 
	l1.print(); 

	List_Int::iterator i1 = l1.begin(), i2 = l1.begin(); 
	i1++, i2++, i2++, i2++; 
	cout << "i1 points to: " << *i1 << endl; 
	cout << "i2 poinst to: " << *i2 << endl; 
	l1.erase(i1, i2); 
	l1.print(); 

	
	List_Int::iterator i = l1.begin(); 
	//i--; /* Error. */
	//i->; /* Error. */
	//List_Int::iterator i; /* Error. */


	
	list<double> first, second;

  first.push_back (3.1);
  first.push_back (2.2);
  first.push_back (2.9);

  second.push_back (3.7);
  second.push_back (7.1);
  second.push_back (1.4);

  first.sort();
  second.sort();

  cout << "first contains:";
  for (list<double>::iterator it=first.begin(); it!=first.end(); ++it)
    cout << " " << *it;
  cout << endl;

  first.merge(second);

  cout << "first contains:";
  for (list<double>::iterator it=first.begin(); it!=first.end(); ++it)
    cout << " " << *it;
  cout << endl;

  cout << second.size() << endl; 

	return EXIT_SUCCESS; 
}

