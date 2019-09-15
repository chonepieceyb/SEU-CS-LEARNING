#include<iostream>
#include"Rational.h"
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	srand(time(0));
	int x = -100 + rand() % 200, y = -100 + rand() % 200;
	int c = -100 + rand() % 200, d = -100 + rand() % 200;
	cout << "a :" << x << " / " << y<<endl;
	cout << "b :" << c << " / " << d<<endl;
	Rational a(x, y);
	Rational b(c, d);
	cout <<"a :"<<a<<endl;
	cout << "b :" << b << endl;
	cout << a << " + " << b << " = " << a + b << endl;
	cout << a << " - " << b << " = " << a-b<< endl;
	system("pause");
	return 0;
	
}