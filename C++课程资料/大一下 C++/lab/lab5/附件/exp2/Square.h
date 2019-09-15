#ifndef SQUARE_H
#define SQUARE_H
#include<string>
#include"TwoDimensionalShape.h"
using namespace std;
class Square : public TwoDimensionalShape
{
public:
	Square();
	Square(double, double);
	Square(double);
	~Square();
	void setA(const double x)
	{
		a = x;
	}
	double getA()const
	{
		return a;
	}
	void setB(const double x)
	{
		b = x;
	}
	double getB()const
	{
		return b;
	}
	string getSortShape()const
	{
		return TwoDimensionalShape::getSortShape();
	}
	virtual double getArea()const;
	virtual void print()const;
protected:
	double a, b;
	void setSortShape(const string a = "Square")
	{
		TwoDimensionalShape::setSortShape(a);
	}
};
#endif
