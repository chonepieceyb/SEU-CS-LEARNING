#ifndef MYDERIVED1_H
#define MYDERIVED1_H
#include"MyBase1.h"
using std::cout;
using std::endl;
class MyDerived1 : public MyBase1
{
public:
	MyDerived1()
	{
		cout<<"...First layer derived Object is created!"<<endl;
	}
	~MyDerived1()
	{
		cout<<"...First layer derived Object is destroyed!"<<endl;
	}
};
#endif