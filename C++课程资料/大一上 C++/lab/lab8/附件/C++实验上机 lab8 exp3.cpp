#include<iostream>
using namespace std;
void swap1(int a, int b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
void swap2(int a, int b)
{
	int* temp = new int;
	*temp = a;
	a = b;
	b = *temp;
	delete temp;
}


void swap3(int*a, int*b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void swap4(int*a, int*b)
{
	int* temp = new int;
	*temp = *a;
	*a = *b;
	*b = *temp;

}
void swap5(int&a, int&b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}
int main()
{
	int a = 10, b = 5;
	int*p = &a, *q = &b;
	swap1(a, b);
	cout << a << " " << b << endl;
	a = 10, b = 5;
	a = 10, b = 5;
	p = &a, q = &b;
	swap2(a, b);
	cout << a << " " << b << endl;
	swap3(p, q);
	cout << *p << " " << *q << endl;
	a = 10, b = 5;
	p = &a, q = &b;
	swap4(&a, &b);
	cout << a << " " << b << endl;
	a = 10, b = 5;
	p = &a, q = &b;
	swap(a, b);
	cout << a << " " << b;
	system("pause");
	return 0;
}