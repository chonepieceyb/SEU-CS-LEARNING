#include"Date.h"
#include<iostream>
#include<string>
using namespace std;
const int Date::days[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };  //方便月份和数组的下标对应
Date::Date(int month, int day, int year)
{
	setDate(month, day, year);
}
void Date::setDate(int mm, int dd, int yy)
{
	if (mm >= 1 && mm <= 12)
		month = mm;
	else
		throw invalid_argument("Month must be 1-12");  //标准错误类的一个
	if (yy >= 1900 && yy <= 2100)
		year = yy;
	else
		throw invalid_argument("Year must be 1900-2100");
	if ((month == 2 && leapYear(year) && dd >= 1 && dd <= 29) || (dd >= 1 && dd <= days[month]))
		day = dd;
	else
		throw invalid_argument("Day is out of range for current month and year");
}

Date& Date::operator++()
{
	helpIncrement();
	return*this;
}
Date Date::operator++(int)//  这里返回值
{
	Date temp = *this;
	helpIncrement();
	return temp;
}
const Date& Date::operator+=(int additionalDays)
{
	for (int i = 0;i<additionalDays;++i)
		helpIncrement();    //但是反复调用这个函数可能导致效率问题
	return*this;
}
bool Date::leapYear(int testYear) //这是一个static函数
{
	if (testYear % 400 == 0 || (testYear % 100 != 0 && testYear % 4 == 0))
		return true;
	else
		return false;
}
bool Date::endOfMonth(int testDay) const
{
	if (month == 2 && leapYear(year))
		return testDay == 29;
	else
		return testDay == days[month];
}
void Date::helpIncrement()  //类设计中的层次化
{
	if (!endOfMonth(day))   //对各种可能出现的情况进行判断值得学习
		++day;
	else
		if (month<12)     //如果一次加很多天 怎么解决？
		{
			++month;
			day = 1;
		}
		else
		{
			++year;
			month = 1;
			day = 1;
		}
}
ostream& operator<<(ostream& output, const Date& d)
{
	static string monthName[13] = { "","January","February","March","April","May",
		"June","July","August","September","October","November","December" };    //让下标和类对应
	output << monthName[d.month] << " " << d.day << ", " << d.year;
	return output;
}
int Date::getmonth()
{
	return month;
}
int Date::getday()
{
	return day;
}
int Date::getyear()
{
	return year;
}
