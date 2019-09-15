#include<iostream>
using namespace std;
int main()
{
	cout << "请输入一个5位数";
	int number, Numarrays[5];
	cin >> number;
	int pos1 = 0;
	while (number>0)
	{
		Numarrays[pos1++] = number % 10;
		number = number / 10;
	}
	pos1 -= 1;   // 关键点要减去多加上的那个数
	int flag = 1, pos = 0;
	while (pos<pos1&&flag==1)
	{
		if (Numarrays[pos++] == Numarrays[pos1--])
			flag = 1;
		else flag = 0;
	}
	if (flag == 1)
		cout << endl << "该五位数是一个回文数";
	else
		cout << endl << "该五位数不是一个回文数";
	system("pause");
	return 0;
}
