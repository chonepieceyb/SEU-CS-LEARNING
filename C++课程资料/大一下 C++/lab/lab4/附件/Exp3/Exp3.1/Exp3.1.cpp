#include<iostream>
using namespace std;
class MyBase3 {
	int x;
	void fun1() { cout << "MyBase3-- - fun1()" << endl; }
protected:
	int y;
	void fun2() { cout << "MyBase3-- - fun2()" << endl; }
public:
	int z;
	MyBase3(int a=1, int b=2, int c=3) { x = a; y = b; z = c; }
	int getX() { cout << "MyBase3-- - x:" << endl; return x; }
	int getY() { cout << "MyBase3-- - y:" << endl; return y; }
	int getZ() { cout << "MyBase3-- - z:" << endl; return z; }
	void fun3() { cout << "MyBase3-- - fun3()" << endl; }
};
class MyDerived1 : public MyBase3 {
	int p;
public:
	MyDerived1(int a) : p(a)
	{};
	int getP() { cout << "MyDerived-- - p:" << endl; return p; }
	void disply()
	{
		cout << p << " " << getX() << " " << getY() << " " << getZ() << " " << endl
			<< endl;
		fun2();
		fun3();
	}
};
int main()
{
	MyDerived1 a(3);
	a.disply();
	cout << a.getX() << " " << a.getP() << " " << a.getY() << " " << a.getZ() << endl;
	return 0;
}