#include<iostream>
using namespace std;
int power(int, int);
int power(int base, int exponent)
{
	if (exponent == 1)
		return base;
	else
		return base*power(base, exponent - 1);
}
int main()
{
	int base, exponent;
	cout << "please enter a base and an exponent:";
	cin >> base >> exponent;
	cout << base << " raised to the " << exponent << " is " << power(base, exponent);
	system("pause");
	return 0;
}