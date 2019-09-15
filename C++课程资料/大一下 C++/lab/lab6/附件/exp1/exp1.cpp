#include<iostream>
#include"QuickSort.h"
#include<cstdlib>
#include<ctime>
using namespace std;
template<typename T>
void PrintArray(const T* t_Tarray, int t_isize)
{
	for (int i = 0;i < t_isize;i++)
		cout << t_Tarray[i]<< ", ";
	cout << endl;
}
int main()
{
	srand(time(0));
	const int SIZE = 20;
	QuickSort<int> process1;
	int m_iTest[SIZE] = { 0 };
	for (int i = 0;i < SIZE;i++)
	{
		m_iTest[i] = rand() % 1000 + 1;
	}
	process1.quicksort(m_iTest, 0, SIZE - 1);
	QuickSort<double> process2;
	double m_dTest[SIZE];
	for (int i = 0;i < SIZE;i++)
	{
		m_dTest[i] = rand() % 1000 + 0.3;
	}
	process2.quicksort(m_dTest, 0, SIZE - 1);
	PrintArray<int>(m_iTest, SIZE);
	PrintArray<double>(m_dTest, SIZE);
	system("pause");

}