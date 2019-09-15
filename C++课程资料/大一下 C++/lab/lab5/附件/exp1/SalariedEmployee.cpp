#include<iostream>
#include"SalariedEmployee.h"
using namespace std;
SalariedEmployee::SalariedEmployee(const string& first, const string& last, const string& ssn, const int mm, const int dd, const int yy, double salary)
	:Employee(first, last, ssn,mm,dd,yy) //初始化参数列表的赋值顺序优先
{
	setWeeklySalary(salary);
}
void SalariedEmployee::setWeeklySalary(double salary)
{
	if (salary >= 0)
		weeklySalary = salary;
	else
		throw invalid_argument("Weekly salary must be >=0.0");
}
double SalariedEmployee::getWeeklySalary()const
{
	return weeklySalary;
}
double SalariedEmployee::earnings()const
{
	return getWeeklySalary();
}
void SalariedEmployee::print()const
{
	cout << "Salaried employee: ";
	Employee::print();  //当要访问基类的同名函数的时候 适用域作用符
	cout << "\nweekly salary: " << getWeeklySalary();
 }