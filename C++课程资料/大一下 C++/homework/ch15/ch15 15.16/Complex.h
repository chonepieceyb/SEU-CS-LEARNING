#ifndef COMPLEX_H
#define COMPLEX_H
#include<iostream>
using namespace std;
class Complex
{
	friend ostream& operator<<(ostream&, const Complex&);
	friend istream& operator >> (istream&, Complex&);
private:
	int m_iReal;
	int m_iImaginary;
	int m_iFlag;
public:
	Complex(const int=0, const int=0);

};
#endif // !COMPLEX_H

