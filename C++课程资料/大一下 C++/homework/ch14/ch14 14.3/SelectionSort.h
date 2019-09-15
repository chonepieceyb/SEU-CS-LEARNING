#pragma once
#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include<iostream>
using namespace std;
template<typename T>
class SelectionSort
{
private:
	void swap(T& m_T1, T& m_T2)
	{
		T t_T3= m_T1;
		m_T1 = m_T2;
		m_T2 = t_T3;
	}
public:
	void selectionsort(T* ,const int);
};

template<typename T>
void SelectionSort<T>::selectionsort(T* m_Tarray, const int t_iSIZE)
{
	if (m_Tarray == nullptr || t_iSIZE <= 0)
	{
		cout << "The data you enter is wrong\n";
		return;
	}
	else
	{
		for (int i = 0;i < t_iSIZE - 1;i++)
		{
			int t_ismallestpos = i;
			for (int t_iindexpos = i + 1;t_iindexpos < t_iSIZE;t_iindexpos++)
			{
				if ( m_Tarray[t_iindexpos] < m_Tarray[t_ismallestpos] )
					t_ismallestpos = t_iindexpos;
			}
			swap(m_Tarray[i], m_Tarray[t_ismallestpos]);
		}
	}
}
#endif // !SELECTIONSORT_H

