#ifndef SEQQUEUE_H
#define SEQQUEUE_H
#include<iostream>
using namespace std;
const int defaltSize = 20;
template<class T>
class SeqQueue
{
public:
	SeqQueue(int size = defaltSize);
	~SeqQueue();
	bool isEmpty()
	{
		if (front == rear)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if ((rear + 1) % maxSize == front)  //如果队尾在对头的前面，从队尾插入
			return true;
		else
			return false;
	}
	bool enQueue(const T& x); //入列
	bool deQueue(T& x); //出列
	bool getFront(T& x);  //取出队头
	void makeEmpty()
	{
		front = rear = 0;
	}
private:
	int maxSize;
	int front;
	int rear;
	T * element;
};
template<class T>
SeqQueue<T>::SeqQueue(int size) :maxSize(size),front(0),rear(0)
{
	//申请动态数组
	element = new T[maxSize];
	if (element == nullptr)
	{
		cout << "申请空间失败";
		exit(1);
	}
}
template<class T>
SeqQueue<T>::~SeqQueue()
{
	if (element != nullptr)
	{
		delete[] element;
		element = nullptr;
	}
}
template<class T>
bool SeqQueue<T>::enQueue(const T& x)
{
	if (isFull())
		return false;
	else
	{
		
		element[rear] = x;
		rear = (rear + 1) % maxSize;
		return true;
	}
}
template<class T>
bool  SeqQueue<T>::deQueue(T& x)
{
	if (isEmpty())
		return false;
	else
	{
		x = element[front];
		front = (front + 1) % maxSize;
	}
}
template<class T>
bool  SeqQueue<T>::getFront(T& x)
{
	if (isEmpty())
		return false;
	else
	{
		x = element[front];
	}
}
#endif // !SEQQUEUE_H
#pragma once
