#include<iostream>
#include"BasePlusCommissionEmployee.h"
using namespace std;
BasePlusCommissionEmployee::BasePlusCommissionEmployee(const string& first, const string& last, const string& ssn, const int mm, const int dd, const int yy, double sales, double
	rate, double salary) :CommissionEmployee(first, last, ssn,mm,dd,yy, sales, rate)//我们看到再类继承中，构造函数往往也要包含基类的构造函数的参数，并且用基类的构造函数进行初始化
{
	setBaseSalary(salary);
}
void BasePlusCommissionEmployee::setBaseSalary(double salary)
{
	if (salary >= 0.0)
		baseSalary = salary;
	else
		throw invalid_argument("Salary must be >=0.0");
}
double BasePlusCommissionEmployee::getBaseSalary()const
{
	return baseSalary;
}
double BasePlusCommissionEmployee::earnings()const //多态
{
	return getBaseSalary() + CommissionEmployee::earnings();  //再加上之前的earnings
 }
void BasePlusCommissionEmployee::print()const//多态
{
	cout << "base-salaried commission employee: ";
	CommissionEmployee::print();
	cout << " ,base salary:" << getBaseSalary();
 }