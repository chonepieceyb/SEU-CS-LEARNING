#include<iostream>
#include<iomanip>
#include<vector>
#include<typeinfo>
#include"BasePlusCommissionEmployee.h"
#include"CommissionEmployee.h"
#include"Date.h"
#include"Employee.h"
#include"SalariedEmployee.h"
#include<windows.h>
using namespace std;
int main()
{
	SYSTEMTIME system;
	GetLocalTime(&system);
	cout << fixed << setprecision(2);
	vector<Employee*>employees(3);
	employees[0] = new SalariedEmployee("John", "Smith", "111-11-1111", 6, 15, 1944,800);
	employees[1] = new CommissionEmployee("Sue", "Jones", "333-33-3333", 5, 8, 1954, 10000, .06);
	employees[2]=new BasePlusCommissionEmployee("Bob", "Lewis", "444-44-4444",3,2,1965, 5000, .04, 300);
	for (size_t i=0;i < employees.size();i++)
	{
		employees[i]->print();
		if (((employees[i]->getdate()).getmonth()) == system.wMonth)
		{
			cout << "\nHAPPY BIRTHDAT!\n";
			cout << "earned $" << employees[i]->earnings()+100 << endl<<endl;
		}
		else
			cout << "\nearned $" << employees[i]->earnings() << endl << endl;
    }
	getchar();
	return 0;
}