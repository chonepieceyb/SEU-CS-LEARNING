#pragma once
#ifndef RATIONAL_H
#define RATIONAL_H
#include<iostream>
using namespace std;
class Rational
{
	friend ostream& operator<<(ostream&, const Rational&);
private:
	enum SIGN{Nagative=-1,None,Positive};
	int m_inumerator;
	int m_idenominator;
	int getRuducefraction(int, int);
	SIGN m_SIGN;
public:
	Rational(const int = 0,const int  = 1);
	Rational operator+(const Rational&);
	Rational operator-(const Rational&);

};
#endif // !RATIONAL_H
