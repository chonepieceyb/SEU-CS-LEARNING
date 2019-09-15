#ifndef TWODIMENSION_H
#define TWODIMENSION_H
#include<string>
#include"Shape.h"
using namespace std;
class TwoDimensionalShape :public Shape
{
private:
	string SortShape;
	void setDimensionalShape(const DimensionalShape a = TWO)
	{
		Shape::setDimensionalShape(a);
	}
public:
	TwoDimensionalShape();
	~TwoDimensionalShape();
	virtual double getArea()const=0;
	virtual void print()const=0;
	DimensionalShape getDimensionalShape()const
	{
		return Shape::getDimensionalShape();
	}
	void setSortShape(const string x)     //为了减少函数调用的次数 采用inline形式
	{
		SortShape = x;
	}
	string getSortShape()const
	{
		return SortShape;
	}

};
#endif
