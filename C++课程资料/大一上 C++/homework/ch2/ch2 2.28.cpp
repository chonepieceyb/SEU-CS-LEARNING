#include<iostream>
using namespace std;
int main()
{
	int A[5] = { 0 };
	cout << "Please Enter an intger of five-digit ";
	int a;
	cin >> a;
	int n = a, i = 0;
	while (n != 0)
	{
		A[i] = n % 10;
		n = n / 10;
		i++;
	}
	i -= 1;
	for (i;i >= 0;i--)
		cout << A[i] << "   ";
	system("pause");
	return 0;
}