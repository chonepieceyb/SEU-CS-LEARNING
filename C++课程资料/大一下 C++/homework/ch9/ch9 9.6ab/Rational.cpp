#include<iostream>
#include"Rational.h"
#include<exception>
#include<cmath>
using namespace std;
int Rational::getRuducefraction( int t_inumerator, int t_idenominator)
{
	int m_inum = t_inumerator;
	int m_ideno = t_idenominator;
	int t_imaxdivision=1;
	int t_itemp;
	if (t_inumerator == t_idenominator)   //并没有 0的特殊情况
	{
		t_imaxdivision = t_inumerator;
		return t_imaxdivision;
	}
	else
	{
		t_itemp = abs(t_inumerator - t_idenominator);
		if (t_inumerator < t_idenominator)
			getRuducefraction(t_inumerator, t_itemp);
		else
			getRuducefraction(t_idenominator, t_itemp);

	}
	
	
}
Rational::Rational( int t_inumerator ,  int t_idenominator )
{
	m_inumerator = t_inumerator;
	m_idenominator = t_idenominator;  //储存的是真实值
	try
	{
		if (t_idenominator == 0)
			throw invalid_argument("The denominator can't not be set to zero!");
	}
	catch (invalid_argument&exc)
	{
		cout << exc.what() << "\n The value of the fraction is now set to zero;\n";
		m_inumerator = 0;
		m_idenominator = 1;
		m_SIGN=None;
		return;
	}
	if (t_inumerator == 0)
	{
		m_inumerator = 0;
		m_idenominator = 1;
		m_SIGN = None;
		return;
	}
	else
	{
		if (t_inumerator*t_idenominator > 0)
			m_SIGN = Positive;
		else
			m_SIGN = Nagative;

		int m_maxdivision= getRuducefraction(abs(t_inumerator), abs(t_idenominator));
		m_idenominator /= m_maxdivision;
		m_inumerator /= m_maxdivision;
	}
}
Rational Rational::operator+(const Rational& t_x)
{
	if (this->m_SIGN == None)
		return t_x;
	else if (t_x.m_SIGN == None)
		return *this;
	else
		return Rational(this->m_inumerator*t_x.m_idenominator + t_x.m_inumerator*this->m_idenominator, this->m_idenominator * t_x.m_idenominator);
}
Rational Rational::operator-(const Rational& t_x)
{
	if (this->m_SIGN == None)
		return t_x;
	else if (t_x.m_SIGN == None)
		return *this;
	else
		return Rational(this->m_inumerator*t_x.m_idenominator - t_x.m_inumerator*this->m_idenominator, (this->m_idenominator * t_x.m_idenominator));
}
ostream& operator<<(ostream&output, const Rational&t_r)
{
	if (t_r.m_SIGN == t_r.None)
		cout << 0;
	else if (t_r.m_SIGN == t_r.Nagative)
		cout << "-" << abs(t_r.m_inumerator) << "/" << abs(t_r.m_idenominator);
	else
		cout  << abs(t_r.m_inumerator) << "/" << abs(t_r.m_idenominator);
	return output;
}