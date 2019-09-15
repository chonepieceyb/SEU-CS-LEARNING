#pragma once
#ifndef TEXTEXCEPTION_H
#define TEXTEXCEPTION_H
#include<stdexcept>
using namespace std;
class TestException :public runtime_error
{
public:
	TestException() :runtime_error("abnormal program termination")
	{}
};
#endif // !TEXTEXCEPTION_H
