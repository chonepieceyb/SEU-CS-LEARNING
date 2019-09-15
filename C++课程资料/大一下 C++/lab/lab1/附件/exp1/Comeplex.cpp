#include"Comeplex.h"
Comeplex:: Comeplex()
{
	a=0;
	b=0;
}
Comeplex:: Comeplex(double x,double y)
{
	a=x;
	b=y;
}
 ostream& operator <<(ostream& output,Comeplex& a)
{
	output<<"("<<a.a<<" ,"<<a.b<<")";
	return output;
}
 Comeplex Comeplex:: operator +( const Comeplex& z) const
 {
	 Comeplex total;
	 total.a=a+z.a;
	 total.b=b+z.b;
	 return total;
 }
Comeplex Comeplex:: operator -( const Comeplex& z) const
{
	Comeplex least;
	least.a =a-z.a;
	least.b =b-z.b;
	return least;
}