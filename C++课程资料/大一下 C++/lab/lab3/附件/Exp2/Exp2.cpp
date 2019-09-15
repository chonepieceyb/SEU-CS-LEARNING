#include<iostream>
#include"HugeInt.h"
using namespace std;
int main()
{
	HugeInt n1(7654321);
	HugeInt n2("7891234");
	HugeInt n3("9999999999999999999999");
	HugeInt n4("1");
	HugeInt result;
	cout << "n1 is " << n1 << "\nn2 is " << n2
		<< "\nn3 is " << n3 << "\nn4 is " << n4
		<< "\nthe result is " << result<<"\n\n";
	if (n1 == n2)
		cout << "n1 is  equal to n2" << endl;
	if (n1 != n2)
		cout << "n1 is not equal to n2" << endl;
	if (n1 < n2)
		cout << "n1 is less than n2" << endl;
	if (n1 <= n2)
		cout << "n1 is less than or equal to n2" << endl;
	if (n1 > n2)
		cout << "n1 is greater than n2" << endl;
	if (n1 >= n2)
		cout << "n1 is greater than or equal to n2" << endl;
	result = n1 + n2;    //为什么返回的是值用连加可以 因为这个式子其参数调用是从右往左调用的，这与cout调用的参数的顺序不同，所以cout就必须要返回引用；
	cout << n1 << " + " << n2 << " = " << result << "\n\n";
	cout << n3 << " + " << n4 << "\n=" << (n3 + n4) << "\n\n";
	result = n1 + 9;
	cout << n1 << " + " << 9 << " = " << result << endl;
	result = n2 + "10000";
	cout << n2 << " + " <<"10000" << " = " << result << endl;
	system("pause");
}