#include<iostream>
#include<cstring>
#include<cassert>
#include"String.h"
using namespace std;

String::String(const char* const s)
{
	length = strlen(s);
	sPtr = new char[length + 1];
	strcpy_s(sPtr, length + 1, s);
	return;
}
String::String(const String &s)
{
	length=s.length;
	if(sPtr!=NULL)
	{delete[]sPtr;
	sPtr=NULL;}
	sPtr=new char[length+1];
	strcpy_s(sPtr,length+1,s.sPtr);
	return;
}
String::~String()
{
	delete[] sPtr;
   sPtr=NULL;
}
const String& String:: operator=(const String& s) 
{
 	length=s.length;
	if(sPtr!=NULL)
	{delete[]sPtr;
	sPtr=NULL;}
    sPtr=new char[length+1];
	strcpy_s(sPtr,length+1,s.sPtr);
	return *this;
}    // ????
  String& String:: operator+(const String &s) const
{
    static String temp;//必须要用static 变量 但是如果再调用一次+运算的话可能会对同一个内存再进行new 运算
	if(temp.sPtr!=NULL)
	{
		delete[]temp.sPtr;
	    temp.sPtr=NULL;
	}
	temp.length=length+s.length;
	temp.sPtr=new char[temp.length+1];
	if(temp.sPtr!=NULL)
	{
		strcpy_s(temp.sPtr,temp.length+1,sPtr);
	    strcat_s(temp.sPtr, temp.length + 1,s.sPtr);
	}
	else
		cout<<"fail";
	return temp;               //有析构函数，导致局部变量被析构了 2大问题返回局部变量的引用或者指针 内存泄露问题
}
ostream& operator<<(ostream &output,const String &s)
{
	output<<s.sPtr;
	return output;
}

	

