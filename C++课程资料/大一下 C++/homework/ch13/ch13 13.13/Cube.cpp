#include<iostream>
#include"Cube.h"
#include<iomanip>
using namespace std;
Cube::Cube()
{
	setA(0.0);
	setB(0.0);
	setC(0.0);
	setSortShape();
}
Cube::Cube(double x, double y, double z) :a(x), b(y), c(z)
{
	setSortShape();
}
Cube::Cube(double x) : a(x), b(x), c(x)
{
	setSortShape();
}
Cube::~Cube()
{}
double Cube::getArea()const
{
	return getA()*getB() + getA()*getC() + getC()*getB();
}
double Cube::getVolume()const
{
	return getA()*getB()*getC();
 }
void Cube::print()const
{
	cout << "The shape is£º " << getSortShape() << "\n";
	cout << "The area is: " << getArea() << "\n";
	cout << "The volume is: " <<  getVolume() << "\n";
 }
