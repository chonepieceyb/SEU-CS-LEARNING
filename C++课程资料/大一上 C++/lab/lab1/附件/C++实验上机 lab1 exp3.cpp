#include<iostream>
using namespace std;
int main()
{
	int a, b;
	cout << "Pleast input two number a,b:\n";
	cin >> a >> b;
	if (a%b == 0)
		cout << "a is a multiple of b";
	else
		cout << "a is not a multiple of b";
	system("pause");
	return 0;
}
