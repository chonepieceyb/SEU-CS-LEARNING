#include<iostream>
#include"CommissionEmployee.h"
using namespace std;
CommissionEmployee::CommissionEmployee(const string& first, const string& last, const string& ssn, const int mm, const int dd, const int yy, double sales, double rate) :Employee(first, last, ssn, mm, dd, yy) //允许对父类进行初始化
{
	setGrossSales(sales);
	setCommissionRate(rate);
}
void CommissionEmployee::setGrossSales(double sales)
{
	if (sales >= 0.0)
		grossSales = sales;
	else
		throw invalid_argument("Gross sales must be >=0.0");
}
double CommissionEmployee::getGrossSales()const
{
	return grossSales;
}
void CommissionEmployee::setCommissionRate(double rate)
{
	if (rate >= 0.0&&rate<1.0)
		commissionRate = rate;
}
double CommissionEmployee::getCommissionRate()const
{
	return commissionRate;
}
double CommissionEmployee::earnings()const//计算收入
{
	return getCommissionRate()*getGrossSales();
}
void CommissionEmployee::print()const //打印
{
	cout << "commission employee: ";
	Employee::print();   //用到父类的函数
	cout << "\ngross sales: " << getGrossSales()
		<< "; commission rate; " << getCommissionRate();
}