#pragma once
using namespace std;
#include<iostream>
#include<string>;
class employ
{
private:
	string firstname;
	string lastname;
	 int salary;
public:
	employ(string, string,  int);
	void setfirstname(string);
	string getfirstname();
	void setlastname(string);
	string getlastname();
	void setsalary(int);
	int getsalary();
	void raise(double);
	void display();

};