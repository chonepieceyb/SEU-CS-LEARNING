#include<iostream>
#include"Time.h"
#include<iomanip>;
using namespace std;
Time:: Time()
{
	second=0;
	minute=0;
	hour=0;
}
Time:: Time(int a,int b,int c)
{
	second=a;
	minute=b;
	hour=c;
}
void Time:: setsecond(int x)
{
	second =x;
}
	int Time:: getsecond(void)
	{
		return second;
	}
	void Time:: setminute(int x)
	{
		minute =x;
	}
	int Time:: getminute(void)
	{
		return minute;
	}
	void Time:: sethour(int x)
	{
		hour =x;
	}
	int Time:: gethour(void)
	{
		return hour;
	}
	void Time:: tick(void)
	{
		second+=1;
		minute+=second /60;
		second %= 60;
		hour+=minute/60;
		minute %=60;
		hour%=24;
	}
	ostream& operator <<(ostream& output, Time& t)
	{
	   output<<setfill('0')<<setw(2)<<(( t.gethour()==0 || t.gethour()==12 )? 12 : t.gethour()%12)<<":"<<setw(2)<<t.getminute()<<":"<<setw(2)
		   <<t.getsecond() <<" "<<(t.gethour()>=12 ? " PM" :"AM");
	   return output;
	}
	  
