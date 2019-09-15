#include<iostream>
#include"Comeplex.h"
int main()
{
	Comeplex z1(10,1);
	Comeplex z2(11,5);
	cout<<z1<<"+"<<z2<<" ="<<z1+z2<<endl;
	cout<<z1<<"-"<<z2<<" ="<<z1-z2<<endl;
	system("pause");
	return 0;
}