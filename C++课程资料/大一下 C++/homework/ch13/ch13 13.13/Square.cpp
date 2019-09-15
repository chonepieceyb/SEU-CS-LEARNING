#include<iostream>
#include"Square.h"
#include<iomanip>
using namespace std;
Square::Square()
{
	a = 0.0;
	b = 0.0;
	setSortShape();
}
Square::Square(double x, double y) :a(x), b(y)
{
	setSortShape();
}
Square::Square(double x) : a(x), b(x)
{
	setSortShape();
}
double Square::getArea()const
{
	return getA()*getB();
}
void Square::print()const
{
	cout << "The shape is£º " << getSortShape() << "\n";
	cout << "The area is: " <<  getArea() << "\n";
}
Square::~Square() {};