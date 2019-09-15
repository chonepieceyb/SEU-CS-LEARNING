#include<iostream>
#include"Employee.h"
#include"Date.h"
using namespace std;
Employee::Employee(const string& first, const string& last, const string& ssn,const int mm,const int dd,const int yy ):firstName(first), lastName(last), socialSecurityNumber(ssn),birthDate(mm,dd,yy)
{
}
void Employee::setFirstName(const string& first)
{
	firstName = first;
}
string Employee::getFirstName()const
{
	return firstName;
}
void Employee::setLastName(const string& last)
{
	lastName = last;
}
string Employee::getLastName()const
{
	return lastName;
}
void Employee::setSocialSecurityNumber(const string& ssn)
{
	socialSecurityNumber = ssn;
}
string Employee::getSocialSecurityNumber()const
{
	return socialSecurityNumber;
}
void Employee::print()const//虚函数关键词virtual 不用再声明一次
{
	cout << getFirstName() << " " << getLastName()<<"\nbirthday: "<<birthDate
		<< "\nsocial security number: " << getSocialSecurityNumber();   //思考为什么不直接返回string?
	
}
Date Employee::getdate()
{
	return birthDate;
}