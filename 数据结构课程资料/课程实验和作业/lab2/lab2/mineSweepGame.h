#ifndef MINESWEEPGAME_H
#define MINESWEEPGAME_H	 
//为了方便后面的找地雷
struct offset
{
	int iOffest;
	int jOffset;
} ;
class MineSweepGame
{
public:
	MineSweepGame();
	~MineSweepGame();
	bool click(int rows, int cols);					 //用户点击地雷的操作
	void reflashMineMatrix(); //刷新，重新输出矩阵
	int  isGameOver();	   //返回m_isGameOver这个flag
	void restartGame();   //重新开始游戏的函数
	
private:
	offset move[8];
	int** m_mineMatrix ; //用来储存地雷信息的矩阵	  -1表示地雷 0表示不是地雷(-1和0都没有被点击） 无穷表示这个点被点击过了 
 	int m_mineSizeA;        //地雷矩阵的行数
	int m_mineSizeB;        //地雷矩阵的列数
 	int m_mineNum; 	  //地雷的数目
	int m_isClicked; // 已经被点击的点的数目;

	int m_isGameOver;   // 用来判断游戏是否结束的 -1表示游戏还没结束 0表示
	void chooseLevel(); 
    int countMineNum(int i, int j);  //计算第 i行 j列周围的地雷的数目，注意
	void creatMine(); //在矩阵里面填地雷; 
	void noneMineExpand(int i,int j);
};


#endif