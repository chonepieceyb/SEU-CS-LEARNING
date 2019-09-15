#include<iostream>
#include"BinaryTree.h"
#include<fstream>
int main()
{
	BinaryTree myTree('#');
	ifstream fin;
	fin.open("binaryTree.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "读取文件失败<<endl";
		return 0;
	}
	myTree.creatBinTree(fin);
	cout << "从文件中创建一棵二叉树\n" << endl;
	cout << "在屏幕上输出一棵二叉树" << endl;
	myTree.turnToMatrix();
	cout << "二叉树存入数组array[" << myTree.Height() << "][" << myTree.getCols() << "]" << endl;
	myTree.printTreeMatrix();
	cout << "度为一的节点的个数为" << myTree.getDegreeOne() << endl;
	system("pause");
}