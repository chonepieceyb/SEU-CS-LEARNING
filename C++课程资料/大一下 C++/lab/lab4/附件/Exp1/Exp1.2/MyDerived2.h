#ifndef MYDERIVED2_H
#define MYDERIVED2_H
#include"MyBase2.h"
using std::cout;
using std::endl;
class MyDerived2 : public MyBase2
{
	MyBase1 a1;
public:
	MyDerived2()
	{
		cout<<"...First layer derived Object is created"<<endl;
	}
	~MyDerived2()
	{
		cout<<"...First layer derived Object is destroyed"<<endl;
	}
};
#endif
			 