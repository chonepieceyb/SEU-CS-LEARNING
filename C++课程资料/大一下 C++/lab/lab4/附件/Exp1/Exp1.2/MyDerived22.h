#ifndef MYDERIVED22_H
#define MYDERIVED22_H
#include"MyDerived2.h"
using std::cout;
using std::endl;
class MyDerived22 : public MyDerived2
{
	 MyBase1 a1;//如果继承得到和包含类得到的东西相同会有什么效果？ 事实证明，同时通过继承和包含得到同一个类（比如这里的MyBase1，它们共存，并且从构造的顺序上看 ”尊老“大于“爱幼” 而析构的顺序和构造的顺序正好相反
public:
	MyDerived22()
	{
		cout<<"...Second layer derived Object is created"<<endl;
	}
	~MyDerived22()
	{
		cout<<"...Second layer derived Object is destroyed"<<endl;
	}
};
#endif