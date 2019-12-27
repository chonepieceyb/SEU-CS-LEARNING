#pragma once
#include<string>
#include<set>
#include"MarcoDef.h"
using namespace std;
class Node
{
public:
	Node(string node_name);
	Node(int node_id, string node_name, string node_value);
	virtual ~Node();
	virtual bool operator<(const Node& n)const;
	ATTRIBUTE_MEMBER_FUNC(int, node_id);
	ATTRIBUTE_MEMBER_FUNC(string, node_value);
	ATTRIBUTE_READ_ONLY(string, node_name)
	virtual set<string> calFirstSet(set<string> called_stack)=0;
	ATTRIBUTE_READ_ONLY(set<string>, firstSet)
	ATTRIBUTE_MEMBER_FUNC(bool, calAgain);
protected:
	int node_id;                       //这一个node的id, 不同的node(包括同类型的node）都是一样的
	string node_value;                // 这个node原始的token的值
	string node_name;                 // 这个节点的名称比如说 S, a , b 等
	set<string> firstSet;            // first集合
	bool calAgain;
};

