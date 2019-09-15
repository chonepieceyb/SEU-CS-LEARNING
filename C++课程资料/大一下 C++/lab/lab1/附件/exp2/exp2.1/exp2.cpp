#include<iostream>
#include"Time.h";
using namespace std;
int main()
{
	Time a(50,59,22);
	cout<<a<<endl;
	for(int i=0;i<50;i++)
	{
		a.tick();
        cout<<a<<endl;
	}

	system("pause");
    return 0;
}