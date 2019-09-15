#ifndef INTEGER_SET_H
#define INTEGER_SET_H
class IntegerSet
{
private:
	int set[101];
	int validEntry( int x) const
	{
		return(x>=0&&x<=100);
	}//用来判断数据是否有效，同是这里把函数定义在类中 使之变成inline 函数可以减少函数调用次数 提高效率
public:
	IntegerSet()
	{
		emptySet();
	} //减少函数的调用 采用 inline 的方式
	IntegerSet(int[],int);
	IntegerSet unionOfSets(const IntegerSet&); //注意 const 的用法
	IntegerSet intersectionOfSets(const IntegerSet&);
	void emptySet();
	void inputSet();
	void insertElement(int);
	void deleteElement(int);
	void printSet()const;
	bool isEqualTo(const IntegerSet&) const;
};
#endif
