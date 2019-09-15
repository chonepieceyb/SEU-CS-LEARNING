#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>
#include"Date.h"
using namespace std;
class Employee
{
public:
	Employee(const string&, const string&, const string&, const int ,const int, const int );
	void setFirstName(const string&);
	string getFirstName()const;
	void setLastName(const string&);
	string getLastName()const;
	void setSocialSecurityNumber(const string&);
	string getSocialSecurityNumber()const;
	virtual double earnings()const = 0;  //abstract base class
	virtual void print()const;
	Date getdate();
private:
	string firstName;
	string lastName;
	string socialSecurityNumber;
	Date birthDate;
};
#endif
