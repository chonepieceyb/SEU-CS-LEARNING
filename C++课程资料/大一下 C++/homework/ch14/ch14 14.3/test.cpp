#include<iostream>
#include"SelectionSort.h"
#include<cstdlib>
#include<ctime>
using namespace std;
template<typename T>
void PrintArray(const T* t_Tarray, int t_isize)
{
	for (int i = 0;i < t_isize;i++)
		cout << t_Tarray[i] << ", ";
	cout << endl;
}
int main()
{
	    srand(time(0));
		const int m_ciArraysize1 = 10;
		SelectionSort<int> process1;
		int m_iTest[m_ciArraysize1] = { 0 };
		for (int i = 0;i < m_ciArraysize1;i++)
		{
			m_iTest[i] = rand() % 1000 + 1;
		}
		process1.selectionsort(m_iTest, m_ciArraysize1);
		SelectionSort<double> process2;
		double m_dTest[m_ciArraysize1];
		for (int i = 0;i < m_ciArraysize1;i++)
		{
			m_dTest[i] = rand() % 1000 + 0.3;
		}
		process2.selectionsort(m_dTest, m_ciArraysize1);
		PrintArray<int>(m_iTest, m_ciArraysize1);
		PrintArray<double>(m_dTest, m_ciArraysize1);
		system("pause");

	
	
}