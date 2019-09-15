#include<iostream>
#include"Item.h"
using namespace std;
void test()
{
	cout << "The test function begins!\n\n";
	try
	{
		Item m_Iitem1(1);
		Item m_Iitem2(2);
		Item m_Iitem3(3);
	}
	catch (runtime_error&test)
	{
		cout << test.what() << '\n';     //因为抛出错误之后 ，类的构造函数自己无法处理 所以让上级处理，Item3的构造函数没有完全执行完
	}                                    //Item3应该没有被构造，自然也不会被析构了
	cout << "\n\nThe end of function test function\n"; 
	return;
}
int main()
{
	test();
	getchar();
}