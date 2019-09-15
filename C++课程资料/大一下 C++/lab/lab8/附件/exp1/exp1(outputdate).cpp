#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream m_OFSoutputdate;
	m_OFSoutputdate.open("D:\\some date and files\\C++上机 2\\lab8\\exp1\\numbers.txt", ios::out);
	if (!m_OFSoutputdate)
	{
		cerr << "The file can't be opened";
		exit(1);
	}
	int x;
	while (cin >> x)
	{
		m_OFSoutputdate << x<<" ";   //不添加" "的话数字不会分开
	}
	m_OFSoutputdate.close();
	return 0;
}