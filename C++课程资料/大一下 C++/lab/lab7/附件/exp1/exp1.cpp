#include<iostream>
#include"TestException.h"
using namespace std;
void throwException()
{
	try
	{
		cout << " Function throwException throws an exception\n";
		throw TestException();
	}
	catch (TestException& test)
	{
		cout << "Exception handled in function throwException"
			<< "\n Function throwException rethrow exception\n";
		cout << test.what()<<endl;
		throw;                              //从throw 语句开始程序直接跳转到上一级的 try catch 语句块中 而且不会执行 throw 之后的语句
		
		
	}
	cout << "The end of the function throwException";
}
int main()
{
	cout << "This is a test"<<endl;
	try
	{
		cout << "\nmain invokes function throwexception\n";
		throwException();
		cout << "The end of the try block in main\n";
	}
	catch (TestException& test)
	{
		cout << "\n\nException handled in main\n";
		//cout << "\nrethrow exception in main";
		cout << test.what();
	}   //主函数不能再抛出异常
	cout << "The end of the test\n";
	system("pause");
}