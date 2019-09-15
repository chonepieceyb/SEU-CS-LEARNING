#include "Chess.h"
#include<iostream>
#include<iomanip>
using namespace std;
Chess::Chess( int s)
{
	
	if (s < 4)
	{
		cout << "棋盘的大小太小" << endl;
		exit(1);
	}
	size = s;
	//分配空间
	chess = new int* [size];
	for (int i = 0; i < size; i++)
	{
		chess[i] = new int[size];
	}
	//初始化
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chess[i][j] = 0;
		}
	}

}


Chess::~Chess()
{
	if (chess != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			if (chess[i] != nullptr)
			{
				delete[]chess[i];
				chess[i] = nullptr;
			}
		}
		delete[]chess;
		chess = nullptr;
	}
}

bool  Chess::Horse(int x,int y)  //进行骑士周游，周游的结果保留在棋盘中。
{
	return Horse(x, y, 1);
}
void Chess::remake(int s)  //重新制作边长为size的棋盘
{
	//把原来的删了
	if (s < 4)
	{
		cout << "棋盘的大小太小" << endl;
		return;
	}
	if (chess != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			if (chess[i] != nullptr)
			{
				delete[]chess[i];
				chess[i] = nullptr;
			}
		}
		delete[]chess;
		chess = nullptr;
	}
	size = s;
	//分配空间
	chess = new int*[size];
	for (int i = 0; i < size; i++)
	{
		chess[i] = new int[size];
	}
	//初始化
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chess[i][j] = 0;
		}
	}
}
void Chess::makeEmpty()  //将棋盘清空（不重新制作）
{
	//全部置为0
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			chess[i][j] = 0;
		}
	}
}

void Chess::printChess() //打印棋盘
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout <<resetiosflags(ios::right) <<setw(4) <<chess[i][j] << " ";
		}
		cout << endl<<endl;
	}
}

bool Chess::findHorsePath(int i1, int j1, int i2, int j2,int& length)
{
	//判断是否合法
	if (i1 < 0 || i1 >= size || i2 < 0 || i2 >= size || j1 < 0 || j1 >= size || j2 < 0 || j2 >= size)
	{
		cout << "输入的起点终点不合法" << endl;
		return false;
	}
	//先构造一个标记矩阵，和chess区分开
	int** path = new int*[size];
	for (int i = 0; i < size; i++)
	{
		path[i] = new int[size];
	}
	//初始化
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			path[i][j] = 0;
		}
	}
	//将起点标记为1;
	length = 0;
	//开始从起点开始进行生长
	growHorsePath(path, size, i1, j1, i2, j2, 0);  //最后一个参数传0

	//生长完毕，从终点开始往回找
	int tempI = i2, tempJ = j2;
	if (path[tempI][tempJ] <= 0)   //如果没走到
	{
		length = -1;
		return false;
	}
	else
	{
		chess[tempI][tempJ] = path[tempI][tempJ];
		while (tempI != i1 || tempJ != j1)  //还没找到终点
		{
			//从8个方向开始,必定能找到一个
			for (int p = 0; p < 8; p++)
			{
				int i = tempI + offsetI[p], j = tempJ+offsetJ[p];
				//判断是否越界
				if (i < 0 || i >= size || j < 0 || j >= size)
					continue;
				else
				{
					if (path[i][j] == (path[tempI][tempJ] - 1))  //找到相邻的就可以直接跳出循环
					{
						chess[i][j] = path[i][j];
						tempI = i;
						tempJ = j;
						length++;
						break;  
					}
				}
			}
		}
		chess[i1][j1] = path[i1][j1];
		return true;
	}
}

bool Chess::Horse(int i, int j, int num)
{
    //递归结束的条件
	if (i < 0 || i >= size || j < 0 || j >= size)   //超出棋盘范围
		return false;
	else if (chess[i][j] != 0)    //已经访问过了
		return false;
	else if (chess[i][j] == 0 && num == size * size)  //这个位置还没有访问而且是最后一个
	{
		chess[i][j] = num;
		return true;
	}
	else
	{ 
		//在八个方向递归搜索
		//只有在成功找到相应的路径之后才改变棋盘的数值
		chess[i][j] = num; //标记这一步访问的位置
		//往8个方向递归试探
		//用贪心算法进行改进
		direction d[8];
		for (int p = 0; p < 8; p++)   //计算可能的方向(下一步可能的 i和j）
		{
			d[p].i = i + offsetI[p];
			d[p].j = j + offsetJ[p];
			d[p].count = countDirection(d[p].i, d[p].j);
		}
		insertSort(d, 8);  //插入排序
		for (int p = 0; p < 8; p++)
		{
			if (d[p].count > 0)
			{
				if (Horse(d[p].i, d[p].j, num + 1))  //成功找到路径知乎返回true
				{
					return true;
				}
			}
		}
		//如果前面的8个方向都没有试探成功执行到这一步
		chess[i][j] = 0;  //去除标记
		return false;  
	}
	
}
int Chess::countDirection(const int i, const int j) //计算下一步八个方向每个方向对应的可能的走法
{
	int count = 0;
	if (i < 0 || i >= size || j < 0 || j >= size)
		return count;
	count++;  //算上自己这个点
	for (int p = 0; p< 8; p++)  //计算8个方向可以走的方向
	{
		int tempI = i + offsetI[p];
		int tempJ = j + offsetJ[p];
		if (tempI >= 0 && tempI < size && tempJ >= 0 && tempJ < size && chess[tempI][tempJ] == 0)
			count++;
	}
	return count;
}
void Chess::insertSort(direction d[], const int n)  //对方向进行排序
{
	for (int i = 1;i < n; i++)
	{
		int pos = i;
		direction tempD = d[pos];
		while (pos > 0)
		{
			if (tempD.count < d[pos - 1].count)
			{
				d[pos] = d[pos - 1];
				pos--;
			}
			else
				break;
		}
		d[pos] = tempD;
	}
}
void Chess::growHorsePath(int** path, int size, int i1, int j1,int i2,int j2,int length)
{
	//从一个点开始不断往周围外扩张，遇到冲突时取小的那一个，扩张到超出边界或者到达目的地结束
	if (i1 < 0 || i1 >= size || j1 < 0 || j1 >= size)  //如果出界了
	{
		return;  //直接返回
	}
	else //没出界
	{
		if (path[i1][j1] != 0 && path[i1][j1] <= length + 1)   //如果当前点不是空的而且当前的值比length+1更小（代表不是最短路径，不需要在扩充下去了）
		{
			return;   //不需要再扩张了,递归结束条件之一
		}
		else  //继续扩张
		{
			if (i1 == i2 && j1 == j2)  //如果到达终点了,更新标记不用再扩张了
			{
				//更新标记
				path[i1][j1] = length + 1;
				return;   
			}
			else
			{
				//更新标记
				path[i1][j1] = length + 1;
				//继续递归往8个方向扩张
				for (int p = 0; p < 8; p++)
				{
					growHorsePath(path, size, i1 + offsetI[p], j1 + offsetJ[p], i2, j2, path[i1][j1]);  //注意最后一个参数传的是当前的i1 j1
				}
			}

		}
	}
}

