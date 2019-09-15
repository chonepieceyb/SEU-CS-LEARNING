#ifndef MYDERIVED11_H
#define MYDERIVED11_H
#include"MyDerived1.h"
using std::cout;
using std::endl;
class MyDerived11 : public MyDerived1
{
public:
	MyDerived11()
	{
		cout<<"...Second layer derived Object is created!"<<endl;
	}
	~MyDerived11()
	{
		cout<<"...Second layer derived Object is destroyed!"<<endl;
	}
};
#endif