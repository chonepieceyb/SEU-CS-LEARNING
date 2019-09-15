#ifndef BASEPLUS_H
#define BASEPLUS_H
#include"CommissionEmployee.h"
class BasePlusCommissionEmployee :public CommissionEmployee
{
public:
	BasePlusCommissionEmployee(const string&, const string&, const string&, const int, const int, const int, double = 0.0, double = 0.0, double = 0.0); //我们看到再类继承中，构造函数往往也要包含基类的构造函数的参数，并且用基类的构造函数进行初始化
	void setBaseSalary(double);
	double getBaseSalary()const;
	virtual double earnings()const; //多态
	virtual void print()const;//多态
private:
	double baseSalary;
};
#endif
