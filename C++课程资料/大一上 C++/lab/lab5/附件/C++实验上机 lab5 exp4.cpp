#include<iostream>
using namespace std;
int gcd2(int p, int q)
{
	if (p%q == 0)
		return q;
	else
		return gcd2(q, p%q);
}
void  gcd(int p, int q, int &divisor)
{
	int temp;
	while (p%q != 0)
	{
		temp = p;
		p = q;
		q = temp%q;
	}
	if (p%q == 0)
		divisor = q;
}
int gcd1(int p, int q)
{
	int temp;
	while (p%q != 0)
	{
		temp = p;
		p = q;
		q = temp%q;
	}
	if (p%q == 0)
		return  q;
}

int main()
{
	int p, q, divisor = 1;
	for (;;)
	{
		cout << "Enter two integers:";
		cin >> p >> q;
		cout << "The greatest common divisor of " << p << " and " << q << " is " << gcd2(p, q);
		cout << endl << endl;
	}
	system("pause");
	return 0;
}