#ifndef RATIONALLIST_H
#define RATIONALLIST_H
#include<iostream>
#include"LinkList.hpp"
#include<iostream>
using namespace std;

class RationalList 
{
public:
	RationalList(int x,int y,int c=1);  
	~RationalList();
	void output(int c = 1);  //默认打印一次循环
	bool getCircle()const
	{
		return isCircle;
	}
private:
	int n; //分母
	int m; //分子
	int count; //打印的循环的次数
	bool compare( LinkList<int>& lastR, int tempR, int tempD, linkNode<int>* & c);
	bool isCircle;
	LinkList<int> rList;
	
};

#endif 


