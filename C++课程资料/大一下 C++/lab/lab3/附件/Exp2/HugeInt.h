#ifndef HUGEINT_H
#define HUGEINT_H
#include<iostream>
using std::ostream;
class HugeInt
{
	friend ostream& operator<<(ostream&, const HugeInt&);
public:
	HugeInt(long = 0);
	HugeInt(const char*);
	HugeInt operator +(const HugeInt&)const; //注意这里没有返回引用
	HugeInt operator +(int)const; //只能使用 HugeInt + int 而不能颠倒 因为这不是友元函数
	HugeInt operator +(const char*)const;
	bool operator >(const HugeInt& a)const;
	bool operator >=(const HugeInt&)const;
	bool operator <(const HugeInt& )const;
	bool operator <=(const HugeInt& )const;
	bool operator !=(const HugeInt& )const;
	bool operator ==(const HugeInt& )const;
	int getlength()const
	{
		int length = n-1;
		while (integer[length] == 0 &&length>=0)     //还要包括0的情况 否则就超出数组的边界了
		{
			length--;
		}
		return length>=0 ?(length + 1):1;
	}  //可能要大量使用 所以使用inline 函数
private:
    static const int n = 30; //为什么不加static 不行？ 只有在有const 限定符号的时候才能在类中为static变量初始化
	short integer[n]; //用short类型的变量节省空间

};
#endif