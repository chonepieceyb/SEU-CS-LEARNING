#include<iostream>
using namespace std;
int main()
{
	const int ArraySize = 10;
	int Num[ArraySize];
	cout << "Please enter ten integers" << endl;
	for (int i = 0;i < 10;i++)
		cin >> Num[i];         //用循环语句输入10个数 i 作为 counter;
	int Max = Num[0];
	int pos = 1; //pos 表示下标
	while (pos < ArraySize)
	{
		if (Max < Num[pos])
			Max = Num[pos];
		pos++;
	}
	cout << "The largest number is:  " << Max;
	system("pause");
	return 0;


	
}