#include"mineSweepGame.h"
#include<iostream>
#include<limits.h>
#include<ctime>
#include<stdlib.h>
#include<iomanip>
using namespace std;
MineSweepGame::MineSweepGame()
{   

	{
		move[0].iOffest=-1;
		move[0].jOffset=-1;
		
		move[1].iOffest=-1;
		move[1].jOffset= 0;
		
		move[2].iOffest=-1;
		move[2].jOffset=1;
		
		move[3].iOffest=0;
		move[3].jOffset=-1;
		
		move[4].iOffest=0;
		move[4].jOffset=1;
		
		move[5].iOffest=1;
		move[5].jOffset=-1;
		
		move[6].iOffest=1;
		move[6].jOffset=0;
		
		move[7].iOffest=1;
		move[7].jOffset=1;
		}
	chooseLevel();
	if(m_mineNum>m_mineSizeA*m_mineSizeB)  //如果地雷的数目过多
	{
		cerr<<"地雷的数目过多，游戏创建失败"<<endl;
		exit(1);
	}
	// 先创建动态二维数组
	m_mineMatrix= new int* [m_mineSizeA];	  
	if(m_mineMatrix==NULL)
	{
		cerr<<"扫雷游戏矩阵创建失败！/n";
		exit(1);
	}
	else
	{
		for(int i=0;i<m_mineSizeA;i++)
		{
			m_mineMatrix[i]=new int[m_mineSizeB];
		}
	}
    //初始化游戏还么ijieshu
	m_isGameOver=-1; 
	m_isClicked=0; //一开始没有点被点击
	//埋地雷
	creatMine();
	reflashMineMatrix();
}
MineSweepGame::~MineSweepGame()
{

	//把动态二维数组销毁
	if(m_mineMatrix!=NULL)
	{
		for(int i=0;i<m_mineSizeA;i++)
		{
			if(m_mineMatrix[i]!=NULL)
				delete[]m_mineMatrix[i];
		}
		delete m_mineMatrix;
	}
	m_mineMatrix=NULL;
}

 bool MineSweepGame::click(int rows, int cols)				 //用户点击地雷的操作 行从1开始 列从1开始
 {
	 
	 //判断是否越界	
	if(rows>m_mineSizeA || cols>m_mineSizeB ||rows<1 || cols<1)
	{
		cout<<"点击的区域超出雷区了，请尝试重新点击"<<endl;
		return false;
	}
        int i=rows-1, j=cols-1;
		int t_mineFlag=m_mineMatrix[i][j];
		//根据矩阵对点击的情况进行判断
		//如果是碰到已经点击过的点 （无穷）
		if(t_mineFlag==	INT_MAX)
		{
			cout<<"你点击的区域已经点击过了，请尝试重新点击"<<endl;
			return false;
		}
		else if( t_mineFlag==-1)  //如果踩到地雷了
		{
			cout<<"踩到地雷了！ 你输了！ 啦啦啦"<<endl;
			//判断游戏是否结束的flag
			m_isGameOver=0;
			return true;
		}
		else    //如果没踩到地雷
		{
			cout<<"点击成功，请继续游戏"<<endl;
			noneMineExpand(i,j);
			return true;
		}
 }
 void MineSweepGame::reflashMineMatrix() //刷新，重新输出矩阵
 {
    //cout<<"游戏继续，加油！"<<endl;
	//输出显示的矩阵
	//输出行号
	 cout << "   ";
	 for (int i = 0; i < m_mineSizeB; i++)
	 {
		
		 cout << setw(2) << setiosflags(ios::right) << i + 1 << " ";
	 }
	 cout << endl<<endl;
	for(int i=0;i<m_mineSizeA;i++)
	{
		
		cout << setw(2) << setiosflags(ios::right) <<i + 1 << " ";
		for(int j=0;j<m_mineSizeB;j++)
		{
			
			//如果是还没有点击过的点
			int t_mineFlag=m_mineMatrix[i][j];
			if(m_isGameOver== 0 || m_isGameOver==1 )   //如果是游戏失败了，或者是游戏成功了， 输出雷图
			{
				if(	t_mineFlag  == INT_MAX ) //已经点击过的非雷的点，输出其周围的地雷数目
				{
					int count=countMineNum(i, j) ;
					cout<< setw(2) << setiosflags(ios::right) <<count<<" ";
				}
				else if (t_mineFlag==0)   //如果是非雷并且还没被点击
				{
					cout  << setw(2) << setiosflags(ios::right) <<"#"<<" ";
				}
				else  //如果是地雷，因为游戏已经结束了，把地雷的位置公布
				{
					cout << setw(2) << setiosflags(ios::right) <<"*"<<" ";
				}
			}
			//如果游戏还在正常进行
			else
			{
				if(	t_mineFlag  == INT_MAX ) //已经点击过的非雷的点，输出其周围的地雷数目
				{
					int count=countMineNum(i, j);
					cout << setw(2) << setiosflags(ios::right) <<count<<" ";
				}
                else
				{
					cout  << setw(2) << setiosflags(ios::right) <<"#"<<" ";
				}
			}
  
			
		}
		cout<<endl;
	}

 }
 int  MineSweepGame::isGameOver()	   //返回m_isGameOver这个flag
 {
	 if(m_isGameOver==0) //如果游戏失败
	 {
		 cout<<"游戏失败！"<<endl;
		 return 0;
	 }
	 else if(m_isGameOver==1)
	 {
		  cout<<"恭喜你，你赢了!"<<endl;
		  m_isGameOver=1;
		  return 1;
	 }
	 else   //如果游戏正常进行 
	 {
		//判断游戏是否成功
		 //如果已经点完了除了地雷之外的点
		 if(m_isClicked+m_mineNum>=m_mineSizeA*m_mineSizeB)
		 {
			 cout<<"恭喜你，你赢了!"<<endl;
			 m_isGameOver=1;
			 return 1;
		 }
		 else 
		 {
			 //cout<<"游戏继续"<<endl;
			 return -1;
		 }
	 }
 }
 void  MineSweepGame::chooseLevel()	 //选择游戏难度
 {
	 cout<<"请选择游戏难度, 在键盘上输入1 表示简单难度， 2表示普通难度， 3表示困难难度， 4表示自定义难度"<<endl;
	 int t_level;
	 cin>>t_level;
	 switch(t_level)
	 {
	 case 1:
		 m_mineSizeA=4;
		 m_mineSizeB=4;
		 m_mineNum=1;
		 break;
	 case 2:
		 m_mineSizeA=7;
		 m_mineSizeB=7;
		 m_mineNum=8;
		 break;
	 case 3:
		 m_mineSizeA=12;
		 m_mineSizeB=12;
		 m_mineNum=20;
		 break;
	 case 4:
		 cout<<"你选择自定义难度，请输入行数，列数，地雷数目(行数，列数最好小于100)"<<endl;
		 cin >> m_mineSizeA >> m_mineSizeB>>m_mineNum;
		 break;
	 default:
		  cout<<"你输入错误，将默认为简单难度"<<endl;
		 	 m_mineSizeA=4;
		 	 m_mineSizeB=4;
		 	 m_mineNum=1;
		 	 
	 }
	 
 }
 void MineSweepGame::restartGame()   //重新开始游戏的函数
 {
     cout<<"重新开始游戏！祝你好运"<<endl;
	 
	 //先把原来的数组销毁
	 //把动态二维数组销毁
	 if(m_mineMatrix!=NULL)
	 {
	 	for(int i=0;i<m_mineSizeA;i++)
	 	{
	 		if(m_mineMatrix[i]!=NULL)
	 			delete[]m_mineMatrix[i];
	 	}
	 	delete m_mineMatrix;
	 }
	 chooseLevel();
	 //创建新的数组
	  	if(m_mineNum>m_mineSizeA*m_mineSizeB)  //如果地雷的
	  	{
	  		cerr<<"地雷的数目过多，游戏创建失败"<<endl;
	  		exit(1);
	  	}
	  	// 先创建动态二维数组
	  	m_mineMatrix= new int* [m_mineSizeA];	  
	  	if(m_mineMatrix==NULL)
	  	{
	  		cerr<<"扫雷游戏矩阵创建失败！/n";
	  		exit(1);
	  	}
	  	else
	  	{
	  		for(int i=0;i<m_mineSizeA;i++)
	  		{
	  			m_mineMatrix[i]=new int[m_mineSizeB];
	  		}
	  	}
	      //初始化游戏还么ijieshu
	  	m_isGameOver=-1; 
	  	m_isClicked=0; //一开始没有点被点击
	  	//埋地雷
	  	creatMine();
		reflashMineMatrix()	;
 }

int  MineSweepGame::countMineNum(int i, int j)  //计算第 i行 j列周围的地雷的数目，注意边角
{
	 int count=0;
	 //左上角
	 int tempi=i,tempj=j;
	 for(int p=0;p<8;p++)//查找8个方向
	 {
		 tempi=i+move[p].iOffest;
		 tempj=j+move[p].jOffset;
		 //判断是否越界
		 if(tempi<0||tempi>=m_mineSizeA||tempj<0 ||tempj>=m_mineSizeB)
		 {
			 continue;
		 }
		 else
		 {
			 if(m_mineMatrix[tempi][tempj]==-1) //如果是地雷
			 {
				
				 count++;
			 }
		 }
	 }
	 return count;
}
void  MineSweepGame::creatMine() //在矩阵里面填地雷; 
{
    srand(time(0));
	int tempNum=0; //已经步的地雷数目
	int tempI,tempJ;
	while(tempNum<m_mineNum)
	{
		//用伪随机数随机产生地雷的坐标
		tempI=rand()%m_mineSizeA;
		tempJ=rand()%m_mineSizeB; 
		m_mineMatrix[tempI][tempJ]=-1;  //布雷
		tempNum++;
	}
	//把其它的地方设置成0
	for(int i=0; i<m_mineSizeA;i++)
	{
		for(int j=0; j<m_mineSizeB;j++)
		{
			if(m_mineMatrix[i][j]!=-1) //如果不是雷
			   m_mineMatrix[i][j]=0;
		}
	}

}
void MineSweepGame::noneMineExpand(int i,int j)  //非雷区域的扩张
{
	if (i < 0 || i >= m_mineSizeA || j < 0 || j >= m_mineSizeB)
		return;
	if (m_mineMatrix[i][j] == -1 || m_mineMatrix[i][j]==INT_MAX)//如果是雷的话,或者已经点击过了
		return;
	else  //如果不是雷并且不是已经点击过的区域
	{
		//标记 
		m_mineMatrix[i][j] = INT_MAX;
		m_isClicked++;
		if (countMineNum(i, j) != 0)  //如果不是周围没有雷
		{
			return;
		}
		else
		{
            int tempi, tempj;
			for (int p = 0; p < 8; p++)//查找8个方向
			{
				tempi = i + move[p].iOffest;
				tempj = j + move[p].jOffset;
				//判断是否越界
				if (tempi < 0 || tempi >= m_mineSizeA || tempj < 0 || tempj >= m_mineSizeB)
				{
					continue;
				}
				//递归调用
				else
				{
						noneMineExpand(tempi, tempj);
				}
		    }
		}
	}
}




















