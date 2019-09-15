#ifndef MINHEAP_H
#define MINHEAP_H
#include<iostream>
using namespace std;
const int defaultSize = 20;
template<class T>
class MinHeap
{
public:
	MinHeap(const int max);
	MinHeap(T arr[], int num, int max);
	~MinHeap();
	bool insert(const T &x);
	bool removeMin(T& x);
	bool isEmpty()const
	{
		return ( (currentSize == 0) ? true : false);
	}
	bool isFull()const
	{
		return ( (currentSize == maxSize) ? true : false);
	}
	void makeEmpty()
	{
		currentSize = 0;
	}
private:
	T* minHeap;
	int maxSize;
	int currentSize;
	void siftDown(int start, int end);
	void siftUp(int start);
};

template<class T>
MinHeap<T>::MinHeap(const int max)
{
	//确定最大的空间
	maxSize = ((defaultSize < max) ? max : defaultSize);
	//分配空间
	minHeap = new T[maxSize];
	if (minHeap == nullptr)
	{
		cout << "最小堆空间分配失败!" << endl;
		return;
	}
	currentSize = 0;
}

template<class T>
MinHeap<T>::MinHeap(T arr[], int num, int max)
{
	//确定最大的空间
	maxSize = ((defaultSize < max) ? max : defaultSize);
	//判断
	if (num >= maxSize)
	{
		cerr << "数组的数目大于堆的最大数目，错误！";
		exit(1);
	}
	//分配空间
	minHeap = new T[maxSize];
	if (minHeap == nullptr)
	{
		cout << "最小堆空间分配失败!" << endl;
		return;
	}
	currentSize = 0;
	//复制数组的内容
	for (int i = 0; i < num; i++)
	{
		minHeap[i] = arr[i];
		currentSize++;
	}
    //开始向下调整
	int currentSiftPos = (currentSize - 2) / 2;   //从最后一个非叶节点开始,currentSiftPos是最后一个非叶节点的下标
	while(currentSiftPos>=0)
	{
		siftDown(currentSiftPos, currentSize - 1);  //逐步向下调整
		currentSiftPos--;
	}
}

template<class T>
MinHeap<T>::~MinHeap()
{
	if (minHeap != nullptr)
	{
		delete[]minHeap;
		minHeap = nullptr;
	}
}

template<class T>
bool MinHeap<T>::insert(const T &x)
{
	if (isFull())
	{
		cout << "最小堆已满，无法插入" << endl;
		return false;
	}
	minHeap[currentSize] = x;
	currentSize++;
	siftUp(currentSize - 1);  //向上调整
	return true;
}

template<class T>
bool MinHeap<T>::removeMin(T& x)
{
	if (isEmpty())
	{
		cout << "最小堆是空的，无法删除";
		return false;
	}
	x = minHeap[0];
	minHeap[0] = minHeap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}
template<class T>
void MinHeap<T>::siftDown(int start, int end)   //自上而下调整,
//其调整的前提是假设两边的子树都已经是最小堆了
{
	int currentSiftPos = start; //当前正在比较的节点
	int childPos = 2 * currentSiftPos + 1; //当前点的左孩子
	T temp = minHeap[currentSiftPos];  //把值取出来
	
	while (childPos <= end)  //判断的条件是还没有超出范围
	{
	    //左右孩子比较，选一个小的值
		if(childPos<end)    //如果还有右孩子的话
		childPos = ((minHeap[childPos] <= minHeap[childPos + 1]) ? childPos : childPos + 1);
		if (temp <= minHeap[childPos])    //如果当前的节点比它的孩子都小，不用调整了
			break;
		else
		{
			//把小的值上浮
			minHeap[currentSiftPos] = minHeap[childPos];
			currentSiftPos = childPos;
			childPos = 2 * currentSiftPos + 1;
		}

	}
	//将原来的值归位
	minHeap[currentSiftPos] = temp;
} 

//自下而上调整,自下而上算法的条件是整棵树已经是最小堆
template<class T>
void MinHeap<T>::siftUp(int start)
{
	int currentSiftPos = start; 
	T temp = minHeap[currentSiftPos]; //取出当前的值
	int parentPos = (currentSiftPos - 1) / 2; //父节点的值
	while (currentSiftPos > 0)   //最多调整到根节点
	{
		if (temp >= minHeap[parentPos])  //如果比父节点大,不用调整了
			break;
		else
		{
			minHeap[currentSiftPos] = minHeap[parentPos];  //大的节点下沉
			currentSiftPos = parentPos;
			parentPos = (currentSiftPos - 1) / 2;
		}
	}
	//归为
	minHeap[currentSiftPos] = temp;
}
#endif // !MINHEAP_H

