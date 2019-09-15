#ifndef CHESS_H
#define CHESS_H
const int offsetI[8] = { -1,1,2,2,1,-1,-2,-2 };
const int offsetJ[8] = { 2,2,1,-1,-2,-2,-1,1 };
struct direction
{
	int count;
	int i;  
	int j;
};
class Chess
{
public:
	Chess(int size=6);
	~Chess();
	bool Horse(int x,int y);   //进行骑士周游，周游的结果保留在棋盘中。
	void remake(int size);  //重新制作边长为size的棋盘
	void makeEmpty();  //将棋盘清空（不重新制作）
	void printChess(); //打印棋盘
	bool findHorsePath(int i1, int j1, int i2, int j2,int& length);
private:
	bool Horse(int x, int y,int num);  //递归调用的函数,num表示是第几步
	int countDirection(int i, int j); //计算下一步八个方向每个方向对应的可能的走法
	void insertSort(direction d[], int n);   //对方向进行排序
	void growHorsePath(int** path,int size,int i1,int j1,int i2,int j2,int length);   //算最短路径采用生长法
	int size;
	int** chess;
	
};
#endif // !CHESS_H
