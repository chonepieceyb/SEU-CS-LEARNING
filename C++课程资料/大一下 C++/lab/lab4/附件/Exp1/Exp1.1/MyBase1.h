#ifndef MYBASE1_H
#define MYBASE1_H
using std::cout;
using std::endl;
class MyBase1
{
public:
	MyBase1()
	{
		cout<<"...BaseClass1 Object is created!"<<endl;
	}
	~MyBase1()
	{
		cout<<"...BaseClass1 Object is destoryed!"<<endl;
	}
};
#endif