#include<iostream>
using namespace std;
class MyBase31 {
	int a, b, c;
public:
	MyBase31(int x=5, int y=6, int z=7) :a(x), b(y), c(z)
	{
		cout << "¡­BaseClass31 Object is created!" << endl;
		cout << a << " " << b << " " << c << endl;
	}
	~MyBase31() { cout << "¡­BaseClass31 Object is destroyed!" << endl; }
	int geta()
	{
		return a;
	}
	int getb()
	{
		return b;
	}
	int getc()
	{
		return c;
	}
	void set(int x, int y, int z)
	{
		a = x;
		b = y;
		c = z;
	}
};
class MyDerived1 : public MyBase31 {
	MyBase31 X;
	int c;
public:
	MyDerived1(int x) : c(x), MyBase31(x, 8, 9)
	{
		X.set(x, 8, 9);
		cout << "¡­Base Object has been created!" << endl;
		cout << "¡­Member Object has been created " <<X.geta() << " " << X.getb() << " " << X.getc() << endl;
		cout << "¡­Derived Object is created!" << c << endl;
	}
};
int main()
{
	{
		MyDerived1 b(88);
	}
	return 0;
}