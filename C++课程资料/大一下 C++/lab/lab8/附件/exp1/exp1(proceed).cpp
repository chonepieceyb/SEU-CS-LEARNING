#include<fstream>
#include<iostream>
using namespace std;
int main()
{
	const int SIZE = 101;
	int m_inumber[SIZE] = { 0 };
	ifstream m_IFSinput;
	ofstream m_OFSoutput;
	m_IFSinput.open("D:\\some date and files\\C++上机 2\\lab8\\exp1\\numbers.txt", ios::in);
	m_OFSoutput.open("D:\\some date and files\\C++上机 2\\lab8\\exp1\\output.txt");
	if (!m_IFSinput)
	{
		cerr << "The file can't be opened";
		exit(1);
	}
	if (!m_OFSoutput)
	{
		cerr << "The file can't be outputed";
		exit(1);
	}
	int t_itemp;
	while (m_IFSinput >> t_itemp)
	{
		++m_inumber[t_itemp];
	}
	for (int i = 1;i <= SIZE-1;i++)
	{
		if (m_inumber[i] != 0)
			m_OFSoutput << "Number of " << i << " responses: " << m_inumber[i] << endl;
	}
	return 0;
	
}