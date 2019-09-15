#include<iostream>
#include<cmath>
using namespace std;
bool prime(int number)
{
	int total = 1;
	for (int q = 2;q <= pow(number, 0.5);q++)
	{
		if (number%q == 0)
		{
			total = total + 1;
			break;
		}
	}
	if (total>1)
		return false;
	else
		return true;
}
int main()
{
	cout << "The prime number from 1 to 10000 is:" << endl;
	cout << "\t";
	for (int i = 2;i <= 10000;i++)
	{
		if (prime(i))
			cout << i << "\t";
	}
	system("pause");
	return 0;
}