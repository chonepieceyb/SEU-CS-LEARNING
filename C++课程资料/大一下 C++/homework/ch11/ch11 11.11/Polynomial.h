#pragma 
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include<exception>
#include<iostream>
using namespace std;
class Polynomial
{
	friend ostream& operator<<(ostream&, Polynomial);
private:
	int* m_iptrPolarray;
	int m_iMaxexponent;//多项式最高项的系数；
	char m_cX;   //多项式每一项的符号
public:
	Polynomial(const int t_iptrPolarray[]=nullptr, const int t_iMaxexponent=-1,char t_cX='x');
	Polynomial(int);
	Polynomial(const Polynomial&);
	~Polynomial();
	void setMaxexponent(int t_iMaxexponent)          //把该有的set get 函数写好会轻松很多
	{
		if(t_iMaxexponent>=0)
		m_iMaxexponent = t_iMaxexponent;
		else
		{
			cout << "The Max exponent must >0, not set the polynomial\n";
			m_iMaxexponent = -1;
		}
	}
	int getMaxexponent()const
	{
		if (m_iMaxexponent == -1)
		{
			cout << "The polynomial has not been set\n ";
			return -1;
		}
		else
		return m_iMaxexponent;
	}
	void setTerms(const int t_iexponentOfterm,const int t_icoefficient)
	{
		if (t_iexponentOfterm > m_iMaxexponent || t_iexponentOfterm < 0)
		{
			cout << "The value you enter is invalid, can not set the term \n";
			return;
		}
		else
		{
			m_iptrPolarray[t_iexponentOfterm] = t_icoefficient;
			return;
		}
	}
	void addTerms(const int t_iexponentOfterm, const int t_icoefficient)
	{
		if (t_iexponentOfterm > m_iMaxexponent || t_iexponentOfterm < 0)
		{
			cout << "The value you enter is invalid, can not set the term \n";
			return;
		}
		else
		{
			m_iptrPolarray[t_iexponentOfterm] += t_icoefficient;
			return;
		}
	}
	int getTerms(int t_iexponentOfterm)const
	{
		if (t_iexponentOfterm > m_iMaxexponent || t_iexponentOfterm < 0)
		{
			cout << "The exponent you enter doesn't exist , can not get the term \n";
			return 0;
		}
		else
		{
			return m_iptrPolarray[t_iexponentOfterm];
		}
	}
	const int* getWholepolynomial()const
	{
		return m_iptrPolarray;
	}

	Polynomial& operator=(const Polynomial&);
	Polynomial operator+(const Polynomial&)const;
	Polynomial operator-(const Polynomial&)const;
	Polynomial operator*(const Polynomial&)const;
	Polynomial& operator+=(const Polynomial&);
	Polynomial& operator-=(const Polynomial&);
	Polynomial& operator*=(const Polynomial&);
};
#endif // !POLYNOMIAL_H
