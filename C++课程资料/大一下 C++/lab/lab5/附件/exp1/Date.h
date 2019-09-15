#ifndef DATE_H
#define DATE_H
#include<iostream>
using namespace std;
class Date
{
	friend ostream& operator<<(ostream&, const Date&);
public:
	Date(int m = 1, int d = 1, int y = 1900);
	void setDate(int, int, int);
	Date& operator++();
	Date operator++(int);//  这里返回值
	const Date& operator+=(int);
	static bool leapYear(int);
	bool endOfMonth(int) const;
	int getmonth();
	int getday();
	int getyear();
private:
	int month;
	int day;
	int year;
	static const int days[];   //可以直接在类中声明
	void helpIncrement();
};
#endif
