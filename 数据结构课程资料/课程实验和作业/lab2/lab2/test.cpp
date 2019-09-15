#include"mineSweepGame.h"
#include<iostream>
using namespace std;
int main()
{
	cout<<"欢迎来到扫雷游戏，祝你玩的开心！  made by 杨彬"<<endl;
	cout << "游戏提示：#表示还没被点击的区域，数字表示这个区域周围的雷的数目，游戏结束后*表示地雷";
	MineSweepGame myGame;
	bool isContinue=true;
	bool isGameContinue=false;
	int row=0,col=0;
	int isGameOver=-1;
	while(isContinue)
	{
		if (isGameContinue)
		{
			myGame.restartGame();
			isGameContinue = false;
		}
		cout<<"请在键盘上输入你所要点击的区域的行数row 和列数col(r, c从1开始)"<<endl;
		cin>>row>>col;
		myGame.click(row,col);
		isGameOver=myGame.isGameOver();
		myGame.reflashMineMatrix();
		cout<<endl;
		if(isGameOver==0)
		{
			cout<<"你输了，请问是否继续？输入1 继续，0 退出游戏"<<endl;
			int flag;
			cin>>flag;
			if(flag==1)
			{
				isContinue=true;
				isGameContinue=true;
			}
			else
			{
				isContinue=false;
				isGameContinue=false;
				break;
			}
			
		}
		else if (isGameOver == 1)
		{
			cout << "你赢了，请问是否继续？输入1 继续，0 退出游戏" << endl;
			int flag;
			cin >> flag;
			if (flag == 1)
			{
				isContinue = true;
				isGameContinue = true;
			}
			else
			{
				isContinue = false;
				isGameContinue = false;
				break;
			}
		}
		
	}
	cout<<"感谢游玩!如果游戏过程中遇到任何bug，请及时和作者联系，谢谢"<<endl;
	system("pause");
	return 0;
}