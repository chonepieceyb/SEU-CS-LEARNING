#include "Node.h"



Node::Node(string node_name):node_name(node_name)
{
	calAgain = true;
}
Node::Node(int node_id, string node_name, string node_value) :node_id(node_id),node_name(node_name),node_value(node_value)
{
	
}

Node::~Node()
{
}
bool Node::operator<(const Node& n)const {
	return this->node_name < n.get_node_name();
}