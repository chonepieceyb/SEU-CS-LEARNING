#include"RationalList.h"
#include<iostream>

using namespace std;
RationalList::RationalList(int x, int y, int c ):n(x),m(y),count(c),rList(n/m)
{
	if (y == 0 || c <= 0)
	{
		cout << "输入的初始参数错误" << endl;
		exit(1);
	}
	//计算整数部分
	int remainder = x % y;
	int dividend = x / y;
	if (remainder == 0)
	{
		return;
	}

	//计算小数部分的第一位
	dividend = (remainder * 10) / m;
	remainder = (remainder * 10) % m;
	rList.insert(rList.getLength(), dividend);
	LinkList<int> lastR;
	int tempR = remainder;
	int tempD = dividend;
    lastR.insert(lastR.getLength(), tempR);  //把所有的余数都存下来,初始已经存在小数位了
	linkNode<int>* begin = nullptr;  //循环开始的指针
	//计算小数部分
	while (tempR != 0)  //当余数不为0的时候
	{
		tempD = (tempR * 10) / m;
		tempR = (tempR * 10) % m;

		//判断是否到循环尽头
		/*
		if(tempR==remainder && tempD==dividend)  //被除数和余数又同时相同了,这是循环小数的条件,从头开始循环
		{
			rList.getRear()->link = rList.getHead()->link;
			isCircle = true;
			break;
		}

		else if ( tempR == lastR && tempD == lastD)
		{
			rList.getRear()->link = rList.getRear();
			isCircle = true;
			break;
		}
		*/
		if (compare(lastR, tempR, tempD, begin))   //如果找到循环体
		{
			rList.getRear()->link = begin;
			isCircle = true;
			break;
		}
		rList.insert(rList.getLength(), tempD);
		lastR.insert(lastR.getLength(), tempR);
	}
	if (tempR == 0)
		isCircle = false;
	 
}

RationalList::~RationalList()
{

}
void RationalList::output(int c )  //默认打印一次循环
{
	if (c <= 0)
	{
		cout << "输入的循环次数错误" << endl;
		return;
	}
	linkNode<int>* current = rList.getHead()->link;
	linkNode<int>* begin = rList.getRear()->link;
	cout << rList.getHead()->data;
	if (current == nullptr)  //如果没有小数部分
		return;
	cout << ".";
    //有小数部分 打印小数的不循环的部分
	while (current != nullptr && current != begin)
	{
		cout << current->data;
		current = current->link;
	}
	if (current == nullptr && !isCircle)
	{
		cout << "\n是有限小数";
		return;
	}
	for (int i = 0; i < c; i++)   //打印循环部分
	{
		cout << current->data;  //打印begin；
		current = current->link;	
		//打印剩下的
		while (current != nullptr && current != begin)
		{
			cout << current->data;
			current = current->link;
		}
	    if(i<c-1)  //最后一次打印不重置
		{
			current = begin;   //循环小数又回到头了
		}
	}
	if (current == begin && isCircle)   //循环体打印完了
	{
		cout << "..." << endl;
		cout << "是无限循环小数，循环体为";
		cout << current->data;
		current = current->link;
		while (current != nullptr && current != begin)
		{
			cout << current->data;
			current = current->link;
		}
	}
	
}
bool RationalList::compare( LinkList<int> &lastR, int tempR, int tempD,linkNode<int>* &c)
{
	int l = 0;  //已经比较的次数
	if (lastR.getLength() != rList.getLength())
	{
		cout << "出现不知名错误" << endl;
		return false;
	}
	else if (lastR.isEmpty() || rList.isEmpty())
		return false;
	else
	{
		linkNode<int>* currentR = lastR.getHead()->link;
		linkNode<int>* currentD = rList.getHead()->link;
		while (l < rList.getLength()&& currentD!=nullptr&& currentR!=nullptr)
		{
			if (currentD->data == tempD && currentR->data == tempR)
			{
				c= currentD;
				return true;
			}
			else
			{
				currentD = currentD->link;
				currentR = currentR->link;
				l++;
			}
		}
		return false;
	}

}
