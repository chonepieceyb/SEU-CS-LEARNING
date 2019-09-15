#ifndef CUBE_H
#define CUBE_H
#include<string>
#include"ThreeDimensionalShape.h"
using namespace std;
class Cube : public ThreeDimensionalShape
{
public:
	Cube();
	Cube(double,double,double);
	Cube(double);
	~Cube();
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
	void setC(const double x)
	{
		c = x;
	}
	double getC()const
	{
		return c;
	}
	string getSortShape()const
	{
		return ThreeDimensionalShape::getSortShape();
	}
	virtual double getArea()const;
	virtual double getVolume()const;
	virtual void print()const;
protected:
	double a, b,c;
	void setSortShape(const string a = "Cube")
	{
		ThreeDimensionalShape::setSortShape(a);
	}
};
#endif
