#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H
#include<iostream>
using namespace std;
template<typename T>
class MergeSort
{
private:
	void SwapSort(T& t_T1, T& t_T2)  //只剩下两个数的时候
	{
		if (t_T1 > t_T2)
		{
			T t_T3 = t_T1;
			t_T1 = t_T2;
			t_T2 = t_T3;
			return;
		}
		else
			return;
	}
	
	int Divide(const int t_iFirst, const int t_iSize)
	{
		if (t_iSize <=2)
		{
			cout << "Can't be divided\n";
			return -1;
		}
		else
		{
			return ((2*t_iFirst + t_iSize-1)/2 );           //分割后的位置 中项
		}
	}
	void Merge( T* const,const int,const int,const int,const int);
public:
	void mergesort(T*, const int, const int = 0);


};

template<typename T>
void MergeSort<T>::Merge( T* const t_Tarray ,const int t_iFirst1 ,const int t_iSize1,const int t_iFirst2, const int t_iSize2)
{
	int t_iSize = t_iSize1 + t_iSize2;
	T* t_Tarray1 = nullptr;
	T* t_Tarray2 = nullptr;
	t_Tarray1 = new T[t_iSize1];
	int pos1 = 0;
	for (int i = t_iFirst1;i <t_iFirst1 + t_iSize1;i++)
	{
		t_Tarray1[pos1++] = t_Tarray[i];
	}
	t_Tarray2= new T[t_iSize2];
	int pos2 = 0;
	for (int i = t_iFirst2;i <t_iFirst2 + t_iSize2;i++)
	{
		t_Tarray2[pos2++] = t_Tarray[i];
	}
	int t_iPos= t_iFirst1 ,t_iPos1 = 0, t_iPos2 =0;
	while (t_iPos1 <t_iSize1 || t_iPos2 < t_iSize2)
	{
		if (t_iPos1 <  t_iSize1 && t_iPos2 <  t_iSize2)
		{
			if (t_Tarray1[t_iPos1] < t_Tarray2[t_iPos2])
				t_Tarray[t_iPos++] = t_Tarray1[t_iPos1++];
			else
				t_Tarray[t_iPos++] = t_Tarray2[t_iPos2++];
		}
		else if(t_iPos2>=  t_iSize2&&t_iPos1 <  t_iSize1)
			t_Tarray[t_iPos++] = t_Tarray1[t_iPos1++];
		else
			t_Tarray[t_iPos++] = t_Tarray2[t_iPos2++];
	}
	if (t_iPos == t_iFirst1 + t_iSize)
	{
		if (t_Tarray1 != nullptr)
		{
			delete[]t_Tarray1;
			t_Tarray1 = nullptr;
		}
		if (t_Tarray2 != nullptr)
		{
			delete[]t_Tarray2;
			t_Tarray2 = nullptr;
		}
		return;
	}
	else
	{
		cout << "Merge failed\n";
		if (t_Tarray1 != nullptr)
		{
			delete[]t_Tarray1;
			t_Tarray1 = nullptr;
		}
		if (t_Tarray2 != nullptr)
		{
			delete[]t_Tarray2;
			t_Tarray2 = nullptr;
		}
		return;
	}
}
template<typename T>
void MergeSort<T>::mergesort(T* t_Tarray, const int t_iSize, const int t_iFirst)
{
	if (t_Tarray == nullptr|| t_iFirst<0)
	{
		cout << "error!\n";
			return;
	}
	else if (t_iSize == 1)                             //边界
	{
		return;
	}
	else if (t_iSize == 2)
	{
		SwapSort(t_Tarray[t_iFirst], t_Tarray[t_iFirst + 1]);
		return;
	}
	else
	{
		int t_iFlagPos = Divide(t_iFirst, t_iSize);
		int t_iFirst1 = t_iFirst, t_iSize1 = t_iFlagPos - t_iFirst + 1;
		int t_iFirst2 = t_iFlagPos + 1, t_iSize2 = t_iSize - t_iSize1;
		return(mergesort(t_Tarray, t_iSize1, t_iFirst1), mergesort(t_Tarray, t_iSize2, t_iFirst2), Merge(t_Tarray, t_iFirst1, t_iSize1, t_iFirst2, t_iSize2));
	}
}

#endif // !MERGESORT_H

