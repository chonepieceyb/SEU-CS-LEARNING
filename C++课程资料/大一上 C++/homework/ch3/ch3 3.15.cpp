#include<iostream>
using namespace std;
class Date
{
private:
		int year;
	    int month;
		int days;
public:
	Date(int, int, int);
	void setyear(int);
	int getyear(void);
	void setmonth(int);
	int getmonth(void);
	void setdays(int);
	int getdays(void);
	void displayDate(void);
	
};
int main()
{
	Date Today(2018, 1, 3);
	Today.displayDate();
	system("pause");
	return 0;
	
}
Date::Date(int Y, int M, int D)
{
	setyear(Y);
	setmonth(M);
	setdays(D);
	return;
}
void Date::setyear(int Y)
{
	year = Y;
	return;
}
int Date::getyear(void)
{
	return year;
}
void Date::setmonth(int M)
{
	if (M >= 1 && M <= 12)
		month = M;
	else
		month = 1;
	return;
}
int Date::getmonth(void)
{
	return month;
}
void Date::setdays(int D)
{
	days = D;
	return;
}
int Date::getdays(void)
{
	return days;
}
void Date::displayDate(void)
{
	cout << getmonth() << "/" << getdays() << "/" << getyear();
}
