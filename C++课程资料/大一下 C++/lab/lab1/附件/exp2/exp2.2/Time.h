#ifndef TIME_H
#define TIME_H

 class Time
{
	friend void tick(Time&t);
	friend std::ostream& operator <<(std::ostream& output,  Time& t) ;
private:
	int second;
	int minute;
	int hour;
public:
	Time();
	Time(int,int,int);
	void setsecond(int);
	int getsecond(void);
	void setminute(int);
	int getminute(void);
	void sethour(int);
	int gethour(void);
	
};
#endif