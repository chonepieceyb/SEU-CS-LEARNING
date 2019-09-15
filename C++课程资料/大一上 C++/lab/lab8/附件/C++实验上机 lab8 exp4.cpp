#include<iostream>
using namespace std;
int getsum1(int a, int b)
{
	int temp = a+b;
	return temp;

}
int* getsum2(int a, int b)
{
	int temp = a + b;
	return &temp;
}
int* getsum3(int a, int b)
{
	int*temp = new int;
	*temp = a + b;
	return temp;
}
int getsum4(int a, int b)
{
	int * temp = new int;
	*temp = a + b;
	return *temp;
}
int getsum5(int a, int b)
{
	int sum = a + b;
	int& temp = sum;
	return temp;
}
int main()
{
	int a = 1, b = 2;
	int sum;
	sum = getsum1(a, b);
	cout << "getsum1 " <<sum <<endl;
	int*ptr= getsum2(a, b);
	sum = *ptr;
	cout << "getsum1 " << sum << endl;
	sum = *getsum3(a, b);
	cout << "getsum1 " << sum << endl;
	sum = getsum4(a, b);
	cout << "getsum1 " << sum << endl;
	sum = getsum5(a, b);
	cout << "getsum1 " << sum << endl;
	system("pause");
}