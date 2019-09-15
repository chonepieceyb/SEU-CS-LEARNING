#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	double principle = 24.00, amount = 24.00;
	double rate = .09;
	int years = 1626;
	cout << setprecision(2);
	for (years = 1626;years <= 2010;years++)
	{
		if (years >= 1626)
			amount = amount + amount*rate;
		cout << setw(4) << years << setw(21) << amount << endl;

	}
	getchar();
	return 0;
}