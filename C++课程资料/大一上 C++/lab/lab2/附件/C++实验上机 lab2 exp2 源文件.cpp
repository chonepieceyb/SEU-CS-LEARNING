#include"employ.h"
#include<iostream>
#include<string>
using namespace std;
employ::employ(string First, string Last, int salary)
{
	setfirstname(First);
	setlastname(Last);
	setsalary(salary);
}
void employ::setfirstname(string First)
{
	firstname = First;
}
string employ::getfirstname()
{
	return firstname;
}
void employ::setlastname(string Last)
{
	lastname = Last;
}
string employ::getlastname()
{
	return lastname;
}
void employ::setsalary(int S)
{
	salary = S;
}
int employ::getsalary()
{
	return salary;
}
void employ::raise(double R)
{
	int newsalary = getsalary()*(1 + R);
	setsalary(newsalary);
}
void employ::display()
{
	cout << getfirstname() << " " << getlastname() << ";";
	cout << " Yearly Salary: " << getsalary();
}
int main()
{
	employ Employ1("Bob", "Jones", 34500);
	employ Employ2("Susan", "Baker", 37800);
	cout << "Employ1"; Employ1.display();
	cout << endl;
	cout << "Employ2"; Employ2.display();
	cout << endl;
	cout << "Increasing employee salaries by 20 %" << endl;
	Employ1.raise(0.2);
	Employ2.raise(0.2);
	cout << "Employ1"; Employ1.display();
	cout << endl;
	cout << "Employ2"; Employ2.display();
	cout << endl;
	cout << "Increasing employee salaries by 20 %";
	system("pause");
}