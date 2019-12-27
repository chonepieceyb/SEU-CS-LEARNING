#pragma once
#include "token.h"
#include<vector>
#include<fstream>
#include<queue>
#include<iomanip>
struct treeNode {
	treeNode(token& t) :t(t) 
	{}
	treeNode(const treeNode& tn) 
	{ this->t = tn.t; this->width = tn.width; this->child_ptrs = tn.child_ptrs; }
	treeNode()
	{
		t = token(-1, "none", "_");  child_ptrs = vector<int>();
	};
	token t;
	int width;
	vector<int> child_ptrs;
};
class SyntaxTree
{
public:
	SyntaxTree();
	~SyntaxTree();
	int addNode(treeNode& t);
	void outputTreeAsFile(ofstream& fout , int widthset = 8,int heightset=4) {
		getTreeWidth(head);   //计算宽度并保存下来
		outputTreeAsFile(fout, head, widthset, heightset);
	}
private:
	vector<treeNode> nodes;                     //存放节点的实际区域
	int head;                             // head 指向 nodes数组的最后一个索引
	void outputTreeAsFile(ofstream& fout, int  subTree, int widthset = 10, int heigtset = 4);
	int getTreeWidth( int  subTree);
	int getTreeDepth(int subTree);            //获取深度
};

