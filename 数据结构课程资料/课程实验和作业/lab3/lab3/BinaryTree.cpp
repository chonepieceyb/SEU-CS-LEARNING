#include"BinaryTree.h"
#include<iostream>
#include<fstream>
#include"Stack.hpp"
#include<cmath>
#include<iomanip>
using namespace std;
BinaryTree::BinaryTree (T ref)
{
	root = nullptr;
	treeMatrix = NULL;
	refValue = ref;
	height=0;
	cols=0;
}
BinaryTree::~BinaryTree()
{
	deleteTree(root);
	for (int i = 0; i < height; i++)
	{
		if (treeMatrix[i] != NULL)
		{
			delete[] treeMatrix[i];
			treeMatrix[i] = NULL;
		}

	}
	if (treeMatrix != NULL)
		delete[] treeMatrix;
}

void BinaryTree::printNode(BinTreeNode* p)
{
	if (p != nullptr)  //如果不是空指针                                                                                                        
	{
		cout << ".." << p->data;
	}
}
void BinaryTree::creatBinTree(ifstream&  fin, BinTreeNode*& subTree)
{
	T p;
    if(fin>>p)   //如果不是文件结尾的话
	{
		
		if (p != refValue)//如果输入的数据不代表空节点,递归结束的条件
		{
			//建立根节点
			subTree = new BinTreeNode(p);
		    //递归建立左子树
			creatBinTree(fin, subTree->leftChild);
			//递归建立右子树
			creatBinTree(fin, subTree->rightChild);

		}
		else
		{
			return;   //递归结束
		}
	}
	else
	{
		return;
	}
}
void  BinaryTree::inOrder(BinTreeNode* subTree, void(*visit)(BinTreeNode* p))   //中序遍历
{
	if (subTree == NULL)  //递归结束的条件
		return;
    //先递归遍历左子树
	inOrder(subTree->leftChild, visit);
	//访问根节点
	visit(subTree);
	//递归遍历右子树
	inOrder(subTree->rightChild, visit);
}
void BinaryTree::printTreeInOrder(BinTreeNode* subTree)
{
	if (subTree == NULL) //递归结束的条件
		return;

	//如果不是叶节点的话就输出占位符


	//先从右子树开始遍历
	printTreeInOrder(subTree->rightChild);
	//输出根节点
	int k;
	if (getLength(root, subTree, k))
	{
		for (int i = 0; i <  k; i++)
			cout << "   ";
	}
	printNode(subTree);
	cout << endl;

	//递归遍历左子树
	printTreeInOrder(subTree->leftChild);
  
}

int BinaryTree::getHeight(BinTreeNode* subTree)
{
	if (subTree == NULL)   //递归结束的条件
		return 0;
	else
		//否则递归 ，返回1（根节点的高度） + 左右子树中最高的那个
		return 1 + Max<T>(getHeight(subTree->leftChild), getHeight(subTree->rightChild));
}

//放在堆栈里面的节点，增加节点是第几层的第几个以及在完全二叉树下的序号等信息
struct stackNode
{
	BinTreeNode* node;
	int id;
	int row;
	int col;
	stackNode(BinTreeNode* n, int r, int i):node(n),row(r),id(i)
	{
	    col=id-(pow(double(2),r-1)-1);
	}

};
bool BinaryTree::turnToMatrix()
{
	//如果矩阵的指针不是空就返回false 
	if (treeMatrix != NULL)
	{
		cout << "已经转化为矩阵了" << endl;
		return false;
	}
	//建立堆栈,用来存放节点以及节点的一些关键信息
    Stack<stackNode> nodeStack;
	//建立动态二维数组
	//获取树高
	 height = getHeight();
	 cols = static_cast<int>(pow(double(2),height));
	treeMatrix = new T*[height];
	if (treeMatrix == NULL)
	{ 
		cout << "矩阵创建失败" << endl;
		return false;
	}
	for (int i = 0; i < height; i++)
	{
		treeMatrix[i] = new T[cols];
		if (treeMatrix == NULL)
		{
			cout << "矩阵创建失败" << endl;
			return false;
		}
	}
	//对矩阵进行初始化，全部填入0
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<cols;j++)
		{
			treeMatrix[i][j]=refValue;
		}
	}

	//设置的临时变量
	//对topNode进行初始化
	//节点在第几层
//节点在完全二叉树下所对应的序号
	stackNode topNode(root,1,1);
    //将根节点压栈
    nodeStack.push(topNode);
	//循环
	while (!nodeStack.isEmpty() && topNode.node!=NULL)
	{
        //填入数组(对node进行访问）
	    //访问的语句
		int j=int(pow(double(2),height-topNode.row))+(topNode.col-1)*int(pow(double(2),height-topNode.row+1))-1;
		treeMatrix[topNode.row-1][j]=topNode.node->data;
		//先让右子树入堆栈
        if(topNode.node->rightChild!=NULL)  //判空
		{
			//入堆栈
			stackNode tempNode(topNode.node->rightChild, topNode.row+1,topNode.id*2+1);
			nodeStack.push(tempNode);

		}
		//准备进入左子树
		if(topNode.node->leftChild!=NULL)
		{
			//取出节点把topNode赋值
			stackNode tempNode(topNode.node->leftChild, topNode.row +1, topNode.id *2);
		    topNode=tempNode;
		}
		else
		{
			//退堆栈
			nodeStack.pop(topNode);
			
		}
	}
	return true;
}
void  BinaryTree::printTreeMatrix()
{
	if(treeMatrix==NULL)
	{
		cout<<"还没有建立矩阵"<<endl;
	}
	else
	{
		//再建立一个临时矩阵
	int** printMatrix= new int*[height];
	if (printMatrix == NULL)
	{ 
		cout << "矩阵创建失败" << endl;
		return;
	}
	for (int i = 0; i < height; i++)
	{
		printMatrix[i] = new int[cols];
		if (printMatrix == NULL)
		{
			cout << "矩阵创建失败" << endl;
			return;
		}
	}
   //对比两个矩阵
	for(int i=0;i<height;i++)
	{
		int step=int (pow(double(2),height-i-2));
		
		for(int j=0;j<cols;j++)
		{
			
			if(i<height-1)  //第一行区分
			{
				bool isLDot=false;
				bool isRDot = false;
				int leftBegin=0;
				int rightEnd=0;
				if(treeMatrix[i][j]!=refValue)
				{

					printMatrix[i][j]=2;
					if(treeMatrix[i+1][j-step]!=refValue) //如果左子树有
					{
						leftBegin=j-step;
						isLDot=true;
					}
					else
					{
						isLDot=false;
						leftBegin=j+1;
					}
					if(treeMatrix[i+1][j+step]!=refValue)  //如果右子树有
					{
						isRDot=true;
						rightEnd=j+step;
					}
					else
					{
						isRDot=false;
						rightEnd=j-1;
					}
					if(isLDot||isRDot)
					{
						for(int p=leftBegin;p<=rightEnd;p++)
						{
							if(printMatrix[i][p]!=2)
							    printMatrix[i][p]=1;
						}
						//更新j
						j=rightEnd+1;
					}
					
				
				}
				else
					printMatrix[i][j]=0;
			}
			else   //最后一行特殊
			{
				if(treeMatrix[i][j]!=refValue)
					printMatrix[i][j]=2;
				else
					printMatrix[i][j]=0;

			}
		
		}
	}
	ofstream fout;
	fout.open("BinaryTreeOutput.txt", ios::out);
	if (!fout.is_open())
	{
		cout << "文件输出失败！";
		fout.close();
	}
  //根据print矩阵输出
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<cols;j++)
		{
			switch(printMatrix[i][j])
			{
			case 0:
				cout<<" ";
				fout <<" ";
				break;
			case 1:
				cout<<".";
				fout << ".";
			    break;
			case 2:
				cout<<treeMatrix[i][j];
				fout << treeMatrix[i][j];
				break;
			default:
				cout<<" ";
				fout << " ";
			}
		}
		cout<<endl;
		fout << endl;
		//输出直线
		if (i + 1 < height)
		{
			for (int j = 0; j < cols; j++)
			{
				switch (printMatrix[i + 1][j])
				{
				case 0:
				case 1:
					cout << " ";
					fout << " ";
					break;
				case 2:
					cout << "|";
					fout << "|";
					break;
				default:
					cout << " ";
					fout << " ";
				}
			}
			cout << endl;
			fout << endl;
		}
		
	}
	fout.close();
	//delete
	for(int i=0;i<height;i++)
	{
		if(printMatrix[i]!=NULL)
			delete[] printMatrix[i];
		printMatrix[i]=NULL;
		
	}
	if(printMatrix!=NULL)
		delete[] printMatrix;
	}
}

void  BinaryTree::deleteTree(BinTreeNode* &subTree)
{
	if(subTree==NULL)
		return ;
	if(subTree->leftChild==NULL&& subTree->rightChild==NULL)  //递归删除
	{
		delete subTree;
		subTree = NULL;
		return ;
	}
	else
	{
		deleteTree(subTree->leftChild);
		deleteTree(subTree->rightChild);
		delete subTree;
		subTree = NULL;
	}
}
bool BinaryTree::getLength(BinTreeNode* subTree, BinTreeNode* node, int& length) //计算某一节点到其根节点的距离
{
	if (subTree == NULL)
	{
		length = 0;
		return false;
		
	}
	if (node == NULL)
	{
		length = 0;
		return false;
	}
    //递归结束条件
	if (subTree == node)
	{
		length = 0;
		return true;
	}
	else if (subTree->leftChild == node || subTree->rightChild == node)
	{
		length = 1;
		return true;
		
	}
	else
	{
		int length1;
		if (getLength(subTree->leftChild, node, length1))
		{
			length = 1 + length1;
			return true;

		}
		else if (getLength(subTree->rightChild, node, length1))
		{
			length = 1 + length1;
			return true;
			
		}
		else
			return false;
	}
	    
}