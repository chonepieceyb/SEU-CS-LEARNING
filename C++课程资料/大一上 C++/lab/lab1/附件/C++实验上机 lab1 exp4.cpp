#include<iostream>
using namespace std;
int main()
{
	int a[20], number;
	int i = 0;
	cout << "please input a number:";
	cin >> number;
	while (number>0)
	{
		a[i++] = number % 10;
		number = number / 10;
	};

	for (i-=1;i >= 0;i--)
		cout << a[i] << " ";
	system("pause");
	return 0;

}