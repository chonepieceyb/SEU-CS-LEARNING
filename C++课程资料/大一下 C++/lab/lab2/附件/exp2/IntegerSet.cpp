#include<iostream>
#include"IntegerSet.h"
using namespace std;
#include<iomanip>
IntegerSet::IntegerSet(int array[],int size)
{
	emptySet();
	for(int i=0;i<size;i++)
	insertElement(array[i]);
}
IntegerSet IntegerSet:: unionOfSets(const IntegerSet& r)
{
	IntegerSet temp;
	for(int n=0;n<101;n++)
	  if(set[n]==1||r.set[n]==1)
		  temp.set[n]=1;
	return temp;
}
IntegerSet IntegerSet:: intersectionOfSets(const IntegerSet& r)
{
	IntegerSet temp;
	for(int i=0;i<101;i++)
		if(set[i]==1 &&r.set[i]==1)
			temp.set[i]=1;
	return temp;
}
void IntegerSet:: emptySet()
{
	for(int i=0;i<101;i++)
		set[i]=0;
}
void IntegerSet:: inputSet()
{
	int number;
	do
	{
		cout<<"Enter an element(-1 to end); ";
		cin>>number;
		if(validEntry(number))
			set[number]=1;
		else 
			if(number !=-1)
			cerr<<"Invalid Element\n";
	}while(number!=-1);
	cout<<"Entry complete\n";
}
void IntegerSet:: insertElement(int k)
{
   if(validEntry(k))
	   set[k]=1;
   else
	   cerr<<"Invalid insert atttempted!\n";
}
void IntegerSet:: deleteElement(int k)
{
	if(validEntry(k))
	set[k]=0;
	else
	cerr<<"Invalid insert atttempted!\n";
}
void IntegerSet:: printSet()const
{
	int x=1;
	bool empty=true; //用来判断是否为空
	cout<<"{";
	for(int u=0;u<101;u++)
	{
			if(set[u])
			{
				cout<<setw(4)<<u<<( x%10==0 ? "\n" : "");//用来控制一行打印10个数
				empty=false;
				x++;
			}
	}
	if(empty)
	   cout<<setw(4)<<"----";
	cout<<setw(4)<<"}"<<'\n';
}
bool IntegerSet:: isEqualTo(const IntegerSet& r) const
{
	for(int i=0;i<101;i++)
		if(set[i]!=r.set[i])
			return false;
    return true; //直接 return true 即可 不用再加上if(i==101)因为 false 的情况已经没了 新技能get!!
}