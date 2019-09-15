#ifndef MYBASE2_H
#define MYBASE2_H
#include"MyBase1.h"
using std::cout;
using std::endl;
class MyBase2
{
	MyBase1 a1;
public:
	MyBase2()
	{
		cout<<"...BaseClass2 Object is created!"<<endl;
	}
	~MyBase2()
	{
		cout<<"...BaseClass2 Object is destoryed!"<<endl;
	}
};
#endif