#ifndef MINHEAP_H
#define MINHEAP_H

const int defaultSize = 100;
template<class E>
class MinHeap
{
public:
	MinHeap(int sz=defaultSize);
	MinHeap(E arr[], int n);
	~MinHeap() { delete[]heap; }
	bool Insert(const E&x);
	bool RemoveMin(E& x);
	bool isEmpty()const
	{
		return (currentSize == 0) ? true : false;
	}
	bool isFull()const
	{
		return (currentSize == maxHeapSize) ? true : false;
	}
	void MakeEmpty()
	{
		currentSize = 0;
	}
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};
template<class E>
MinHeap<E>::MinHeap(int sz)
{
	maxHeapSize = (defaultSize < sz) ? sz : defaultSize;
	heap = new E[maxHeapSize];
	currentSize = 0;
}
template<class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
	maxHeapSize = (defaultSize < n) ? n : defaultSize;
	heap = new E[maxHeapSize];
	for (int i = 0; i < n; i++)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}
template<class E>
void MinHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (i <= m)
	{
		if ( j<m && heap[j]>heap[j + 1]) j++;
		if (temp <= heap[i])break;
		else { heap[i] = heap[j]; i = j; i = 2 * j + 1; }
	}
	heap[i] = temp;
}
template<class E>
void MinHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2; E temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)break;
		else {
			heap[j] = heap[i]; j = i; i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}
template<class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)
		return false;
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}
template<class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if (!currentSize)
		return false;
	x = heap[0]; heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}
#endif // !MINHEAP_H


#pragma once
