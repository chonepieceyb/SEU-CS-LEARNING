#ifndef SHAPE_H
#define SHAPE_H
class Shape
{
public:
	enum DimensionalShape { NONE = 0, TWO = 2, THREE = 3 };
	Shape();
	~Shape();
	virtual void print()const=0;
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