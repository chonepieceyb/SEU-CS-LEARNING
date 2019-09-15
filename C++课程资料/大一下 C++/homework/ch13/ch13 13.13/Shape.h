#ifndef SHAPE_H
#define SHAPE_H
class Shape
{
public:
	enum DimensionalShape { NONE = 0, TWO = 2, THREE = 3 };
	Shape();
	~Shape();
	virtual double getArea()const { return 0; }; //虚函数不能只给定义？
	virtual double getVolume()const { return 0; };
	virtual void print()const {};
	DimensionalShape getDimensionalShape()const
	{
		return dimensionalshape;
	}
	void setDimensionalShape(const DimensionalShape a)
	{
		dimensionalshape = a;
	}
private:
	DimensionalShape dimensionalshape;
};
#endif