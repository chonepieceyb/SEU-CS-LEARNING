#include<iostream>
using namespace std;
class Comeplex
{
	friend ostream& operator <<(ostream& output,Comeplex& a);
private:
	double a;
	double b;
public:
	Comeplex();
	Comeplex(double,double);
	Comeplex operator +( const Comeplex&) const;
	Comeplex operator -( const Comeplex&) const;
};
