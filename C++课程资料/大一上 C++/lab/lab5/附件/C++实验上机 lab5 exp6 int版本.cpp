#include<iostream>
using namespace std;
int Fib(int);
int Fib(int n)
{
	if (n == 0)
		return 0;
	else
	{
		if (n == 1)
			return 1;
		else
		{
			int a_2 = 0, a_1 = 1, a = 1;
			for (int i = 2;i <= n;i++)
			{
				a = a_2 + a_1;
				a_2 = a_1;
				a_1 = a;
			}
			return a;
		}
	}
}
int main()
{
	int n;
	for (;;)
	{
		cin >> n;
		cout << "fibonacci(" << n << ") = " << Fib(n) << endl;;
	}
	system("pause");
	return 0;
}