#include"HugeInt.h";
#include<ostream>
using std::cout;
HugeInt::HugeInt(long a)
{
	      //涉及到对后面的修改的时候 一定要设一个临时变量
	if (a >0)
	{
		int temp = a;
		int pos = 0;
		while (temp > 0)
		{
			integer[pos++] = temp % 10;
			temp /= 10;
		}
		for (int i = pos;i < n;i++)
			integer[i] = 0;
	}
	if (a == 0)
		for (int j = 0;j < n;j++)
			integer[j] = 0;
	if (a < 0)
	{
		cout << "给定的参数小于0，不符合要求，该数已经被设定为0\n";
		for (int j = 0;j < n;j++)
			integer[j] = 0;
	}

   return;
}
HugeInt::HugeInt(const char* a)
{
	int flag = 0;
	int pos = 0;
	int length = strlen(a);
	for (int i = 0;i < length;i++)
	{
		if (a[length - 1 - i]<'0' || a[length - 1 - i]>'9')
		{
			cout << "输入的参数不符合要求，输入的参数不是数字,该数已经被设定为0\n";
			for (int i = 0;i < n;i++)
				integer[i] = 0;
			flag = 1;
			break;
		}
		else
		{
			integer[i] = a[length - 1 - i] - '0';
		}
	}
	if (flag == 0)
		for (int j = length;j < n;j++)
			integer[j] = 0;
	return;
    
	}
HugeInt HugeInt::operator +(const HugeInt& a)const
{
	HugeInt result = a;
	int pos = 0;
	while (pos+1 <= getlength() || pos+1 <= a.getlength())
	{
		int temp = result.integer[pos] + integer[pos];
		temp < 10 ? result.integer[pos] = temp : (result.integer[pos] = temp % 10, result.integer[pos + 1] += 1);
		pos++;
	}
	return result;
}
HugeInt HugeInt:: operator +(int a)const
{
	HugeInt result(a);
	return result + *this;
}
HugeInt HugeInt:: operator +(const char* a)const
{
	HugeInt result(a);
	return result + *this;       //这样做事实上多构造了实例， 降低效率
}
bool HugeInt:: operator >(const HugeInt& a)const
{
	int j = getlength() - 1;
	if (getlength() < a.getlength())
		return false;
	else
		if (getlength() > a.getlength())
			return true;
		else
			for (j;j >= 0;j--)
			{
				if (integer[j] > a.integer[j])
				{
					return true;
					break;
				}
				if (integer[j] < a.integer[j])
				{
					return false;
					break;
				}
			}
	if (j < 0)
		return false;
}
bool HugeInt:: operator >=(const HugeInt&a)const
{
	return(!(*this < a));
}
bool HugeInt:: operator <(const HugeInt& a)const
{
	int j = getlength() - 1;
	if (getlength() < a.getlength())
		return true;
	else
		if (getlength() > a.getlength())
			return false;
		else
			for (j;j >= 0;j--)
			{
				if (integer[j] > a.integer[j])
				{
					return false;
					break;
				}
				if (integer[j] < a.integer[j])
				{
					return true;
					break;
				}
			}
	if (j < 0)
		return false;
}
bool HugeInt::operator<=(const HugeInt& a)const
{
	return !(*this > a);
}
bool HugeInt:: operator !=(const HugeInt& a)const
{
	return !(*this == a);
}
bool HugeInt:: operator ==(const HugeInt& a)const
{
	int j = getlength() - 1;
	if (getlength() < a.getlength())
		return false;
	else
		if (getlength() > a.getlength())
			return false;
		else
			for (j;j >= 0;j--)
			{
				if (integer[j] > a.integer[j])
				{
					return false;
					break;
				}
				if (integer[j] < a.integer[j])
				{
					return false;
					break;
				}
			}
	if (j < 0)
		return true;
}
ostream& operator<<(ostream& output, const HugeInt& a)
{
	for (int i = a.getlength() - 1;i >= 0;i--)
		cout <<a.integer[i];
	return output;
}