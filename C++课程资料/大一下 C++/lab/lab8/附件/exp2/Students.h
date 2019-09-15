#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include<fstream>
#include<string>
using namespace std;
class Student
{
	friend ofstream& operator<< (ofstream&, const Student);
public:
	
	Student(int,string,string, double);
private:
	int m_iIDNumber;
	string m_sfirstname;
	string m_slastname;
	double m_dgrade;
};

Student::Student(int t_iIDNumber, string t_sfirstname, string t_slastname, double t_dgrade)
{
	m_iIDNumber = t_iIDNumber;
	m_sfirstname = t_sfirstname;
	m_slastname = t_slastname;
	m_dgrade = t_dgrade;
}
ofstream& operator<< (ofstream& fout, const Student t_student)
{
	fout << t_student.m_iIDNumber << " " << t_student.m_sfirstname << " " << t_student.m_slastname << " "
		<< t_student.m_dgrade << " ";
	return fout;
}
#endif // !STUDENT_H
