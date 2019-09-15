#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int Fatorial(int n)
{
	if (n == 0)
		return 1;
	else
		if (n == 1)
			return 1;
		else
			return n* Fatorial(n - 1);

}
int main()
{
	double total=0;
	double temp = 0;
	int TermNum,x;
	cout << "x= ";
	cin >> x;
	cout << "Please set the accuracy of it ";
	cin >> TermNum;
	for (int i = 0;i <= TermNum;i++)
	{
		temp = pow(x, i);
		total = total + temp / Fatorial(i);
	}
	cout << fixed << setprecision(4) << total;
	system("pause");
	return 0;
}