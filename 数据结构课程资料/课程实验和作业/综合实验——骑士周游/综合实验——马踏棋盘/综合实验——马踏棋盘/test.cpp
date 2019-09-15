#include"Chess.h"
#include<iostream>

using namespace std;
int main()
{
	//测试1
	bool first = true;
	do
	{
		cout << "请输入棋盘的边长(>=4)" << endl;
		int size;
		cin >> size;
		Chess myChess(size);
		if (!first)
		{
			myChess.remake(size);
		}
		cout << "开始进行骑士周游，请输入周游的起点" << endl;
		int i, j;
		cin >> i >> j;
		if (myChess.Horse(i, j))
			cout << "骑士周游成功！" << endl;
		else
			cout << "周游失败" << endl;
		cout << "周游的结果：" << endl;
		myChess.printChess();
		cout << "\n是否继续测试，输入n结束测试进入下一个测试，输入任意字符继续测试" << endl;
		char flag;
		cin >> flag;
		if (flag == 'n')
			break;
		first = false;
	} while (true); 

	//测试2
	bool first2 = true;
	do
	{
		cout << "请输入棋盘的边长(>=4)" << endl;
		int size;
		cin >> size;
		Chess myChess(size);
		if (!first2)
		{
			myChess.remake(size);
		}
		cout << "开始进行寻找两个点之间最短的骑士路径,请输入起点" << endl;
		int i1, j1;
		cin >> i1 >> j1;
		cout << "请输入终点" << endl;
		int i2, j2;
		int length = 0;
		cin >> i2 >> j2;
		if (myChess.findHorsePath(i1, j1, i2, j2, length))
			cout << "成功找到路径!路径长度为: " << length << endl;
		else
			cout << "找不到路径" << endl;
		cout << "骑士的路径的结果：" << endl;
		myChess.printChess();
		cout << "\n是否继续测试，输入n结束测试，输入任意字符继续测试" << endl;
		char flag;
		cin >> flag;
		if (flag == 'n')
			break;
		first2 = false;
	} while (true);
}