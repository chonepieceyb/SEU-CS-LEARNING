#ifndef COMMISSIONEMPLOYEE_H
#define COMMISSIONEMPLOYEE_H
#include"Employee.h"
#include<iostream>
class CommissionEmployee : public Employee
{
public:
	CommissionEmployee(const string&, const string&, const string&, const int, const int, const int, double = 0.0, double = 0.0);
	void setCommissionRate(double);
	double getCommissionRate()const;
	void setGrossSales(double);
	double getGrossSales()const;
	virtual double earnings()const;//计算收入
	virtual void print()const; //打印
private:
	double grossSales;
	double commissionRate;
};
#endif
