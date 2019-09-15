#include<iostream>
using namespace std;
#include"String.h"
int main()
{
	String string1, string2("The date is");
	String string3(" August 1,1993");
	cout<<"string1= string2 + string3\n";
    string1=string2+string3;
	cout<<string2<<endl;
	cout<<"\""<<string1<<"\"=\""<<string2<<"\"+\""<<string3<<"\""<<endl;
	system("pause");
	return 0;
}