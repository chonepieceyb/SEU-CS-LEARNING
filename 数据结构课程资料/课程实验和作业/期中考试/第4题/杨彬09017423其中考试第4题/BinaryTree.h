#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<iostream>
#include"Stack.hpp"
using namespace std;
typedef char T;
struct BinTreeNode
{
	T data;
	BinTreeNode* leftChild;
	BinTreeNode* rightChild;
	BinTreeNode( T d, BinTreeNode* l=nullptr, BinTreeNode* r =nullptr):data(d),leftChild(l),rightChild(r)
	{}

};
//函数模板
template<class Type>
inline Type Max(const Type a, const Type b)
{
	return( a > b ? a : b);
}
class BinaryTree
{
public:
	BinaryTree(T ref); //构造函数建立一棵空的二叉树
	~BinaryTree();
	void creatBinTree(ifstream& fin)  //从文件中读取并构造出一课二叉树
	{
		creatBinTree(fin, root);
	}
	//突然间有一个思考，如果采用这种遍历方式的话可能会造成visit函数破坏树的结构（因为visit可以访问树）
	//并且并没有对visit函数做出什么限制，这会不会带来安全问题
	void inOrder(void(*visit)(BinTreeNode* p))   //中序遍历
	{
		inOrder(root, visit);
	}

	void printTreeInOrder() //采用中序遍历的方法在屏幕上打印打印二叉树
	{
		printTreeInOrder(root);
	}
	int  getHeight() //获取树高的函数
	{
		return getHeight(root);
	}
	bool turnToMatrix();
	void printTreeMatrix();

	int Height()
	{
		return height;
	}
	int getCols()
	{
		return cols;
	}
private:
	BinTreeNode* root; //根节点
	T refValue;
	T ** treeMatrix;
	int height;
	int cols;
	void printNode(BinTreeNode* p);    //打印单个节点的函数
	void creatBinTree(ifstream& in, BinTreeNode*& subTree);
	void inOrder(BinTreeNode* subTree, void(*visit)(BinTreeNode* p));   //中序遍历
	void printTreeInOrder(BinTreeNode* subTree);
	void deleteTree(BinTreeNode* &subTree);
	int getHeight(BinTreeNode* subTree);
	bool getLength(BinTreeNode* subTree, BinTreeNode* node,int &length);


};
#endif // !BINARYTREE_H

