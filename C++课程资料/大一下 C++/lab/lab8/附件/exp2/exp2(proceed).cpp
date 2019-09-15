#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	string m_spath="D:\\some date and files\\C++ио╩З 2\\lab8\\exp2\\";
	string m_sfilename;
	int m_iIDNumber;
	string m_sfirstname;
	string m_slastname;
	double m_dgrade;
	ifstream m_IFSinput;
	cout << "Enter the name of the file:";
	cin >> m_sfilename;
	m_spath += m_sfilename;
	m_IFSinput.open(m_spath, ios::in);
	if (!m_IFSinput)
	{
		cout << "The file can't be opened\n";
		exit(1);
	}
	
	double m_dwholegrade=0;
	int m_inumberofstudent=0;
    while (m_IFSinput >> m_iIDNumber >> m_sfirstname >> m_slastname >> m_dgrade)
	{
		cout << m_iIDNumber << " " << m_sfirstname << " " << m_slastname << " " << m_dgrade << endl;
		m_dwholegrade += m_dgrade;
		++m_inumberofstudent;
	}
	cout << "Class average: " << m_dwholegrade / m_inumberofstudent<<endl;
	system("pause");
	return 0;
}