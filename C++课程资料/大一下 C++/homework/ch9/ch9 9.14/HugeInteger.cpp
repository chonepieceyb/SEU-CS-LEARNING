#include<iostream>
#include"HugeInteger.h"
#include<cstring>
using namespace std;
HugeInteger::HugeInteger( int a )
{
	for (int j = 0;j < 40;j++)
		integer[j] = 0;
	int i = 0;
	while (a > 0)
	{
		integer[i] = a % 10;
		a /= 10;
		i++;
	}
	SIZE = i ;
}
HugeInteger::HugeInteger(const char* a)
{
	if (a[0] == '0'&&strlen(a) == 1)
	{
	    SIZE = 0;
		for (int i = 0;i < 40;i++)
			integer[i] = 0;
	}
	else
	{
		const int size = strlen(a);
		for (int i = size - 1;i >= 0;i--)
			integer[i] = static_cast<int>(a[size - 1 - i] - '0');
		for (int j = size;j < 40;j++)
			integer[j] = 0;
		SIZE = size;
	}
}
HugeInteger HugeInteger::operator +(const HugeInteger& x)
{
	HugeInteger total=*this;
	int pos = 0;
	while (pos <= SIZE - 1 || pos <= x.SIZE - 1)
	{
		int temp = total.integer[pos] + x.integer[pos];
		temp >= 10 ? (total.integer[pos + 1] += 1, total.integer[pos] = (temp % 10)) : total.integer[pos] = temp;
		pos++;
	}
	int size = 0;
	for (int i = 39;i >= 0;i--)
	{
		if (total.integer[i] != 0)
		{
			size = i + 1;
			break;
		}
	}
	total.SIZE = size;
	return total;
}
HugeInteger HugeInteger::  operator +(int a)
{
	HugeInteger x(a);
	return (*this + x);
}
HugeInteger HugeInteger:: operator +(const char* a)
{
	HugeInteger x(a);
	return (*this + x);
}
HugeInteger HugeInteger:: operator -(const HugeInteger& x)
{
	HugeInteger least=*this;
	int pos = 0;
	while (pos <= SIZE-1 || pos <= x.SIZE-1)
	{
		int temp = 0;
		least.integer[pos] >= x.integer[pos] ? temp = least.integer[pos] - x.integer[pos] : 
			(--least.integer[pos+1],temp = 10 + least.integer[pos] - x.integer[pos]);
		least.integer[pos] = temp;
		pos++;
	}
	int size = 0;
	for (int i = 39;i >= 0;i--)
	{
		if (least.integer[i] != 0)
		{
			size = i + 1;
			break;
		}
	}
	least.SIZE = size;
	return least;
}

HugeInteger HugeInteger::operator -(int a)
{
	HugeInteger x(a);
	return (*this - x);
}
HugeInteger HugeInteger::operator -(const char*a)
{
	HugeInteger x(a);
	return (*this - x);
}
bool  HugeInteger:: operator ==(const HugeInteger& x)
{
	if (SIZE == x.SIZE)
	{
		int flag = 1;
		for(int pos=SIZE-1;pos>=0;pos--)
		{
			if (integer[pos] != x.integer[pos])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool HugeInteger:: operator !=(const HugeInteger& x)
{
	return !(*this == x);
}
bool HugeInteger:: operator >(const HugeInteger& x)
{
	if (SIZE > x.SIZE)
		return true;
	if (SIZE < x.SIZE)
		return false;
	if (SIZE == x.SIZE)
	{
		int flag = 1;
		int i = SIZE - 1;
		for (i;i >= 0;i--)
		{
			if (integer[i] < x.integer[i])
			{
				flag = 0;
				break;
			}
			if(integer[i]>x.integer[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0 ||i<0 )
			return false;
		else
			return true;
	}
}
bool HugeInteger::operator <(const HugeInteger& x)
{
	return !(*this > x || *this == x);
}
bool HugeInteger::operator >=(const HugeInteger&x)
{
	return(*this > x || *this == x);
}
bool HugeInteger::operator <=(const HugeInteger& x)
{
	return(*this < x || *this == x);
}
bool HugeInteger::isZero()
{
	if (SIZE == 0)
		return true;
	else
		return false;
}
ostream& operator << (std::ostream&output, HugeInteger&x)
{
	if (x.SIZE == 0)
		cout <<0;
	for (int i=x.SIZE-1;i>=0;i--)
	{
		output << x.integer[i];
	}
	return output;
}
istream& operator >>(std::istream&input, HugeInteger&x)
{
	char* s=new char[40];
	input >> s;
	x = s;
	delete[] s;
	return input;
}