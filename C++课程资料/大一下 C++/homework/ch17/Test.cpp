#include<iostream>
#include<fstream>
#include"MergeSort.h"
#include<vector>
using namespace std;
int main()
{
	ifstream fin1;
	ifstream fin2;
	ofstream fout;
	fout << flush;
	fin1.open("D:\\some date and files\\C++上机 2\\作业\\ch17\\Array1.txt", ios::in);
	fin2.open("D:\\some date and files\\C++上机 2\\作业\\ch17\\Array2.txt", ios::in);
	if (!fin1)
	{
		cout << "The file1 can not be open\n";
		return 0;
	}
	if (!fin2)
	{
		cout << "The file2 can not be open\n";
		return 0;
	}
	vector<int> Array;
	int m_iSize = 0;
	int temp=0;
	
	while (fin1 >> temp)
	{
		Array.push_back(temp);
	}
	
	fin1.close();
	while (fin2 >> temp)
	{
		Array.push_back(temp);
	}
	fin2.close();
	int* m_iptrArray = new int[Array.size()];
	for (int i = 0;i < Array.size();i++)
	{
		m_iptrArray[i] = Array[i];
	}
	MergeSort<int> process;
	process.mergesort(m_iptrArray, Array.size());
	
	fout.open("D:\\some date and files\\C++上机 2\\作业\\ch17\\output.txt", ios::out);
	fout << flush;
	if (!fout)
	{
		cout << "The file1 can not be open\n";
		return 0;
	}
	for (int i = 0;i < Array.size();i++)
	{
		fout << m_iptrArray[i]<<" ";
	}
	fout.close();
	delete[]m_iptrArray;
	return 0;
}