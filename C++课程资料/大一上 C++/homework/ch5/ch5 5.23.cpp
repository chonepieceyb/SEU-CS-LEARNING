#include<iostream>
using namespace std;
int main()
{
	const int n = 9;
	int n_2 = (n + 1) / 2;
	for (int lines = 1;lines <= n_2;lines++)
	{
		for (int i = 1;i <= n_2 - lines;i++)
			cout << " ";
		for (int i = 1;i <= (lines * 2 - 1);i++)
			cout << "*";
		for (int i = 1;i <= n_2 - lines;i++)
			cout << " ";
		cout << endl;
	}
	for (int lines = n_2 - 1;lines >= 1;lines--)
	{
		for (int i = 1;i <= n_2 - lines;i++)
			cout << " ";
		for (int i = 1;i <= (lines * 2 - 1);i++)
			cout << "*";
		for (int i = 1;i <= n_2 - lines;i++)
			cout << " ";
		cout << endl;
	}
	system("pause");
	return 0;

}