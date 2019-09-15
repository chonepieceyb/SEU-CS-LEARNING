#include<iostream>
using std::cout;
using std::endl;
#include"SimpleCalculator.h"
int main()
{
	double a=10.0;
	double b=20.0;
	SimpleCalculator X;
	cout<<"The value of a is: "<<a<<"\n";
	cout<<"The value of b is: "<<b<<"\n\n";
	double addition;
	addition=X.add(a,b); 
	cout<<"Adding a and b yields "<<addition<<"\n";
	double subtraction=X.subtract(a,b);
	cout<<"Subtraction b from a yields "<<subtraction<<"\n";
	double multiplication =X.multiply(a,b);
	cout<<"Multiplying a by b yields "<<multiplication<<"\n";
	double division=X.devide(a,b);
	cout<<"Dividing a by b yields "<<division<<endl;
	system("pause");
	return 0;
	
}
