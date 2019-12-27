#pragma once
#include "Node.h"
#include <vector>
/*
ÖÕ½á·ûÀà
*/
class Terminator :
	public Node
{
public:
	Terminator(string node_name);
	Terminator(int node_id, string node_name, string node_value);
	~Terminator();
	virtual set<string> calFirstSet(set<string> called_stack);

};

