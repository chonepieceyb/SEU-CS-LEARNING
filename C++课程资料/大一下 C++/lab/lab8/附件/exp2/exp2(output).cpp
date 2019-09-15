#include<fstream>
#include"Students.h"
using namespace std;
int main()
{
	ofstream m_OFSoutput;
	m_OFSoutput.open("D:\\some date and files\\C++ио╩З 2\\lab8\\exp2\\studentfiles.txt", ios::out);
	Student m_student1(253, "Bill", "Purple", 88.9);
	Student m_student2(632, "Debbie", "Green", 91.2);
	Student m_student3(412, "Steven", "Red", 94.7);
	Student m_student4(522, "Mike", "Blue", 83.8);
	m_OFSoutput << m_student1 << "\n";
	m_OFSoutput << m_student2 << "\n";
	m_OFSoutput << m_student3 << "\n";
	m_OFSoutput << m_student4 << "\n";
	return 0;
}