#include<iostream>
#include"HashTable.hpp"
#include<ctime>
#include<stdlib.h>
using namespace std;
int main()
{
	srand(time(0)); //中种子
	bool first = true;
	do
	{ 
	cout << "从质数序列{3，7，11，19}中选区一个值" << endl;
	int prim;
	cin >> prim;
	cout << "从{10，20，50}中选取一个n" << endl;
	int n;
	cin >> n;
	HashTable<int, int> myHash(prim, prim+1);
	if (!first)//不是第一次进入循环
		myHash.reMake(prim, prim + 1);
	int x;
	cout << "关键码 : ";
	for (int i = 0; i < n; i++)
	{
		x = 1 + rand() % 1000;
		cout << x << " ";
		myHash.insert(x, x);
	}
	//输出原始数据
	cout << endl;
	myHash.output();
	cout << endl;
	myHash.staticticAnalyse();
	cout << "\n是否停止测试？若停止测试输入n,否则输入任意字符继续实验" << endl;
	char flag;
	cin >> flag;
	if (flag == 'n')
		break;
	first = false;
	cout << "\n\n";
	} while (true);
	system("pause");
		return 0;
}