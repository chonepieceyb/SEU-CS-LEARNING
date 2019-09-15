#include<iostream>
using namespace std;
bool prime(int number)
{
	int total = 1;
	for (int q = 2;q <= number / 2;q++)
	{
		if (number%q == 0)
		{
			total = total + 1;
			break;   //一遇到非1 的因子马上跳出循环
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