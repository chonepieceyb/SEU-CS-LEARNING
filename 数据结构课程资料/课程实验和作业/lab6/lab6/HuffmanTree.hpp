#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include"MinHeap.hpp"
#include<iostream>
#include<string>
#include<fstream>
#include"Stack.hpp"
using namespace std;
template<class T>
struct HuffmanNode
{
	//权值域
	T weight; 
	//指针域，采用类似于静态链表的结构
	int leftChild, rightChild, parent;
	int locate;
	//构造函数
	HuffmanNode():leftChild(-1), rightChild(-1), parent(-1),locate(-1)
	{}   //默认构造
	HuffmanNode(const T& w, const int l=-1, const int r=-1
		,const int p = -1,const int loc=-1):weight(w),leftChild(l),rightChild(r),parent(p),locate(loc)
	{}
	//比较函数的重载
	bool operator<(const HuffmanNode& rh)
	{
		if (weight < rh.weight)
			return true;
		else
			return false;
	}
	bool operator>(const HuffmanNode& rh)
	{
		if (weight > rh.weight)
			return true;
		else
			return false;
	}
	bool operator<=(const HuffmanNode& rh)
	{
		if (weight <= rh.weight)
			return true;
		else
			return false;
	}
	bool operator>=(const HuffmanNode& rh)
	{
		if (weight >= rh.weight)
			return true;
		else
			return false;
	}
	bool operator==(const HuffmanNode& rh)
	{
		if (weight == rh.weight)
			return true;
		else
			return false;
	}
	
};

template<class T>
class HuffmanTree
{
public:
	HuffmanTree(const T arr[],const char D[], int num);  //通过数组来构造哈夫曼树
	~HuffmanTree()
	{
		if (huffmanTree != nullptr)
		{
			delete[] huffmanTree;
			huffmanTree = nullptr;
		}
		if (dictionary != nullptr)
		{
			delete[]dictionary;
			dictionary = nullptr;
		}
	}
	bool findHuffmanCode(const int i, string& code);   //找到某一个节点所代表的哈夫曼编码
	void translateHuffmanCode(ifstream& fin, ofstream& fout);   //从文件中读取数据，并且把翻译结果输出到文件中
	void outputWholeWeight();

private:
	HuffmanNode<T>* huffmanTree;
	char* dictionary; //字符对应的字典
	int root;
	int nums;
	void mergeTree(const int  lchild, const int  rchild, const int  parent);
	//把两个根节点分别是lchild和rchild的子树合成为一棵树，新树的根节点指针为parent，注意parent的参数类型
	
	
};

template<class T>
HuffmanTree<T>::HuffmanTree(const T arr[],const char D[] ,int num) //通过数组来构造哈夫曼树
{
	//根节点先取-1
	root = -1;
	//总结点的个数
	nums = num ;
	//复制字典
	dictionary = new char[nums];
	for (int i = 0; i < nums; i++)
	{
		dictionary[i] = D[i];
	}
	//构建哈夫曼树的静态链表存储空间，根据节点的关系，一共有num个叶节点，整棵树最多就有2*num-1个节点
	huffmanTree = new HuffmanNode<T>[2 * num - 1];
	//将数组前num个赋值为叶节点
	for (int i = 0; i < num; i++)
	{
		huffmanTree[i].weight = arr[i];
		huffmanTree[i].locate = i;
	}
	//构建最小堆
	MinHeap<HuffmanNode<T>>heap(num);
	
	//将所有的节点插入最小堆
	for (int i = 0; i < num; i++)
	{
		heap.insert(huffmanTree[i]); 
	} 
	
	int first, second;
	HuffmanNode<T> firstNode, secondNode;
	int currentSize = num; //当前数组中节点的数目
    //做num- 1次
	for (int i = 0; i < num - 1; i++)
	{
		//取出权值最小的两棵树
		heap.removeMin(firstNode);
		heap.removeMin(secondNode);

		//获取节点的locate；
		first = firstNode.locate;
		second = secondNode.locate;

		//合并两棵树
		mergeTree(first, second, currentSize);
		//将新的树插入堆中
		heap.insert(huffmanTree[currentSize]);
		currentSize++;
	
	}
	if (currentSize != 2 * num - 1)
	{
		cout << "构建的过程中出现未知错误!" << endl;
	}
	root = currentSize-1;
}

template<class T>
bool HuffmanTree<T>::findHuffmanCode(const int i, string& code)
{
	code = ""; //先置空
	if (i >= nums)
		return false;
	//用堆栈实现逆序输出
	Stack<char> S;
	int currentPos = i; //路径上当前的节点
	while (huffmanTree[currentPos].parent != -1)   //找到根节点之后停下来(当当前节点是根节点的时候
	{
		int parentPos=huffmanTree[currentPos].parent; //父指针
		if (huffmanTree[parentPos].leftChild == currentPos)  //如果当前节点是左孩子
		{
			//压入0
			S.push('0');
		}
		else   //如果当前节点是右孩子
		{
			//压入1；
			S.push('1');
		}
		currentPos = parentPos;   //节点向上寻
	}
	//利用堆栈逆序输出
	while(!S.isEmpty())
	{
		char x;
		if (!S.pop(x))
			cout << "出现未知错误！" << endl;
		code += x;
	}
	return true;
}

template<class T>
void HuffmanTree<T>::translateHuffmanCode(ifstream& fin, ofstream& fout)
{
	int currentPos = root;  //当前路径的节点
	char x=0;

	while (fin>>x)  //逐个读入数字
	{
		
		//如果是叶节点


		
			if (x == '0')
				currentPos = huffmanTree[currentPos].leftChild;  //往左边
			else if (x == '1')
				currentPos = huffmanTree[currentPos].rightChild; //往右边找
			else
			{
				cout << "读到非0或者1的字符跳过";
			}
			if (huffmanTree[currentPos].leftChild == -1 && huffmanTree[currentPos].rightChild == -1)
			{
				//找到叶节点了，输入字符
				fout << dictionary[currentPos];
				//重置为根
				currentPos = root;

			}
		
	}
}

template<class T>
void HuffmanTree<T>::mergeTree(const int  lchild, const int  rchild, const int  parent)
{
	//构造新节点权值相加
	huffmanTree[parent].weight = huffmanTree[lchild].weight + huffmanTree[rchild].weight;
	//对于新节点，几下其在数组中的下标,对于旧的节点则不需要
	huffmanTree[parent].locate = parent;
	//挂上去
	//子节点挂到父节点上
	huffmanTree[parent].leftChild = lchild;
	huffmanTree[parent].rightChild = rchild;
    
	//改变子节点的父指针
	huffmanTree[lchild].parent = huffmanTree[rchild].parent = parent;
}
template<class T>
void HuffmanTree<T>::outputWholeWeight()
{
	T total = 0;
	for (int i = 0; i < 2*nums-1; i++)
	{
		total += huffmanTree[i].weight;
	}
	cout << "总权值为" << total << endl;
	cout << "根节点的权值为" << huffmanTree[root].weight;
}
#endif 

