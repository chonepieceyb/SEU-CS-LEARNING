#include<iostream>
#include<iomanip>
#include<vector>
#include"Employee.h"
#include"SalariedEmployee.h"
#include"CommissionEmployee.h"
#include"BasePlusCommissionEmployee.h"
#include"Date.h"
using namespace std;
void virtualViaPointer(const Employee* const);//通过指针访问虚函数
void virtualViaReference(const Employee& );//通过引用访问   猜测 指针可以达到虚函数的效果但是引用不行 猜想错误，指针和引用都可以达到虚函数的效果
int main()
{
	cout << fixed << setprecision(2);
	SalariedEmployee salariedEmployee("John", "Smith", "111-11-1111", 800);
	CommissionEmployee commissonEmployee("Sue", "Jones", "333-33-3333", 10000, .06);
	BasePlusCommissionEmployee basePlusCommissionEmployee("Bob", "Lewis", "444-44-4444", 5000, .04, 300);
	cout << "Employees processed individually ysing static binding:\n\n";
	salariedEmployee.print();
	cout << "\nearned $" << salariedEmployee.earnings() << "\n\n";
	commissonEmployee.print();
	cout << "\nearned $" << commissonEmployee.earnings() << "\n\n";
	basePlusCommissionEmployee.print();
	cout << "\nearned $" << basePlusCommissionEmployee.earnings() << "\n\n";
	vector<Employee*> employees(3);
	employees[0]= &salariedEmployee;
	employees[1]= &commissonEmployee;
	employees[2]= &basePlusCommissionEmployee;
	cout << "Employees processed polymorphically via dynamic binding:\n\n";
	cout << "Virtual function calls mad off base-class pointers:\n\n";
	for (size_t i = 0;i < employees.size();++i)
		virtualViaPointer(employees[i]);
	for (size_t i = 0;i < employees.size();++i)  //emoloyees[i]是一个指针
		virtualViaReference(*employees[i]);
     Employee* a = &salariedEmployee;
	(*a).print();
	cout<<"\nearned $" << (*a).earnings();   //只能采用指针或者引用的方式，如果用小点点的方法不能达到虚函数的效果。
	system("pause");
	return 0;
}
void virtualViaPointer(const Employee*const baseClassPtr)
{
	baseClassPtr->print();
	cout << "\nearned $" << baseClassPtr->earnings() << "\n\n";
}
void virtualViaReference(const Employee&  baseClassRef)
{
	baseClassRef.print();
	cout << "\nearned $" << baseClassRef.earnings() << "\n\n";
}
