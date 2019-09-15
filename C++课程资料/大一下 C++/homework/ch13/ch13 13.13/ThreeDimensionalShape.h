#ifndef THREEDIMENSIONAL_H
#define THREEDIMENSIONAL_H
#include<string>
#include"Shape.h"
using namespace std;
class ThreeDimensionalShape :public Shape
{
private:
	string SortShape;
	void setDimensionalShape(const DimensionalShape a = THREE)
	{
		Shape::setDimensionalShape(a);
	}
public:
	ThreeDimensionalShape();
	~ThreeDimensionalShape();
	virtual double getArea()const { return 0; };
	virtual double getVolume()const { return 0; }
	virtual void print() {};
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