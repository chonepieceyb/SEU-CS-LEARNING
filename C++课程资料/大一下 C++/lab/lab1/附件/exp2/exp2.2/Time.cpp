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
	void  tick(Time&t)
	{
		t.second+=1;
		t.minute+=t.second /60;
		t.second %= 60;
		t.hour+=t.minute/60;
		t.minute %=60;
		t.hour%=24;
	}
	ostream& operator <<(ostream& output, Time& t)
	{
	   output<<setfill('0')<<setw(2)<<(( t.gethour()==0 || t.gethour()==12 )? 12 : t.gethour()%12)<<":"<<setw(2)<<t.getminute()<<":"
		   <<setw(2)<<t.getsecond()<<" "<<(t.gethour()>=12 ? " PM" :"AM");
	   return output;
	}
	  
