#include"RationalList.h"
#include<iostream>
using namespace std;
int main()
{
	RationalList* myList;
	do
	{
		cout << "\n开始测试，请输入分子和分母(!=0)" << endl;
		int n, m;
		cin >> n >> m;
		int c = 1;
        cout << "开始将分数表示为小数" << endl;
		myList = new RationalList(n, m);
		if (myList->getCircle())
		{
			cout << "输入要打印的循环体的次数(>=1)" << endl;

			cin >> c;
		}
		cout << "结果为：" << endl;
		myList->output(c);
		cout << "\n测试结束，请输入n结束测试，输入任意字符继续测试" << endl;
		if (myList != nullptr)
		{
			delete myList;
			myList =nullptr;
		}
		char flag;
		cin >> flag;
		if (flag == 'n')
		{
			break;
		}


	} while (true);
	return 0;
}