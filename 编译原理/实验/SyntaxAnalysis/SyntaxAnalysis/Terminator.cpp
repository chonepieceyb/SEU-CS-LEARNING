#include "Terminator.h"


Terminator::Terminator(string node_name) :Node(node_name)
{

}
Terminator::Terminator(int node_id, string node_name, string node_value):Node(node_id, node_name, node_value)
{

}
Terminator::~Terminator() {

}
set<string> Terminator::calFirstSet(set<string> called_stack ) {
	this->firstSet.insert(node_name);
	return this->firstSet;
 }
