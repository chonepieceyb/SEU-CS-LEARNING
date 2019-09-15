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
	myTree.printTreeMatrix();
	cout << "带权值之和为" << myTree.getWeightLength() << endl;
	system("pause");
}