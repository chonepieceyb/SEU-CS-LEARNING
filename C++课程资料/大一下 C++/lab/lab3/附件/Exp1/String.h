#ifndef STRING_H
#define STRING_H
#include<iostream>
using std::cout; //可以写在句子之间
using std::ostream;
#include<cstring>
#include<cassert> //提供宏assert的定义 在程序关键地方使用这个宏进行断言。如果一处断言被证明为真，程序在标准错误流中输出一条适当的提示信息，并让执行异常终止
class String
{
	friend ostream& operator<<(ostream &output,const String &s);
public:
	String(const char* const s="");//既不能改变指针指向的内容，也不能改变指针的指向,默认构造函数
	String(const String&);//复制构造函数
	~String();
	const String& operator=(const String& );
	 String& operator+(const String&)const;
private:
	char *sPtr;
	int length;
};
#endif