#include<iostream>
using namespace std;
class MyBase {
	int x;
public:
	MyBase(int a) :x(a)
	{}
	int getX() { cout << " " << endl; return x; }
};
class MyDerived : public MyBase {
	int y;
public:
	MyDerived(int a) :y(a), MyBase(a + 4)
	{}
	int getY() { cout << " " << endl; return y; }
};
int main()
{
	MyBase a(2);
	MyDerived b(4); 
	MyBase* p = &a;
	MyDerived* q = &b;
	MyBase &c = a;
	MyDerived &d = b;
	cout << a.getX() << " " << p->getX() << endl;
	cout << b.getY() << " " << q->getY() << b.getX() << " " << q->getX() << endl;
	a = b;
	cout << a.getX() << " " << endl;
	p = q;          //即使用指针赋值也不行
    cout << p->getX() << " " << endl;
	cout << c.getX() << " " << d.getX() << " " << d.getY() << endl;
	return 0;
}