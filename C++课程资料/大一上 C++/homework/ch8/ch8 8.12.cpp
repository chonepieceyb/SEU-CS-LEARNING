#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
using namespace std;
int moveTortoise(int* pos_T_ptr)
{
	int movement = 0;
	int i = 1 + rand() % 10;
	if (i >= 1 && i <= 5)
		movement = 3;
	else
	{
		if (i >= 6 && i <= 7)
			movement = -6;
		else
			movement = 1;
	}
	*pos_T_ptr += movement;
	if (*pos_T_ptr < 1)
		*pos_T_ptr = 1; //if it slip left before 1 ,put it 1;
	return *pos_T_ptr;


}
int moveHare(int* pos_H_ptr)
{
	int movement = 0;
	int i = 1 + rand() % 10;
	if (i >= 1 && i <= 2)
		movement = 0;
	if (i >= 3 && i <= 4)
		movement = 9;
	if (i == 5)
		movement = -12;
	if (i >= 6 && i <= 8)
		movement = 1;
	if (i >= 9 && i <= 10)
		movement = -2;
	*pos_H_ptr += movement;
	if (*pos_H_ptr < 1)
		*pos_H_ptr = 1; //if it slip left before 1 ,put it 1;
	return *pos_H_ptr;
}
int main()
{
	int clock = 1;//act as a clock;
	int pos_T = 1, pos_H = 1;
	int* pos_T_ptr = &pos_T;
	int* pos_H_ptr = &pos_H;
	srand(time(0));
	cout << "BANG !!!!" << endl << "AND THEY'RE OFF!!!!!" << endl;
	pos_H = moveHare(pos_H_ptr);
	pos_T = moveTortoise(pos_T_ptr);
	for (clock;pos_T < 70 && pos_H < 70;clock++)    //during the game
	{

		if (pos_T == pos_H)
		{
			int i = 1;
			for (i = 1;i < pos_T;i++)
				cout << ' ';
			cout << "OUCH!!!";
			i += 1;
			for (i;i <= 70;i++)
				cout << " ";
			cout << setw(5) << "second " << setw(5) << "second " << clock;
			cout << endl;
		}
		else
		{
			if (pos_T<pos_H)
			{
				int i = 1;
				for (i = 1;i < pos_T;i++)
					cout << ' ';
				cout << "T";
				i += 1;
				for (i;i <pos_H;i++)
					cout << " ";
				cout << "H";
				i += 1;
				for (i;i <= 70;i++)
					cout << " ";
				cout << setw(5) << "second " << clock;
				cout << endl;
			}
			else
			{
				int i = 1;
				for (i = 1;i < pos_H;i++)
					cout << ' ';
				cout << "H";
				i += 1;
				for (i;i <pos_T;i++)
					cout << " ";
				cout << "T";
				i += 1;
				for (i;i <= 70;i++)
					cout << " ";
				cout << setw(5) << "second " << clock;
				cout << endl;
			}

		}
		pos_H = moveHare(pos_H_ptr);
		pos_T = moveTortoise(pos_T_ptr);

	}
	if (pos_T >= 70 && pos_H<70)
	{
		int i = 1;
		for (i = 1;i < pos_H;i++)
			cout << ' ';
		cout << "H";
		i += 1;
		for (i;i <70;i++)
			cout << " ";
		cout << "T";
		cout << setw(5) << "second " << clock << endl;
		cout << "TORTOISE WINS!!!YAY!!!";
		cout << endl;
	}
	if (pos_H >= 70 && pos_T<70)
	{
		int i = 1;
		for (i = 1;i < pos_T;i++)
			cout << ' ';
		cout << "T";
		i += 1;
		for (i;i <70;i++)
			cout << " ";
		cout << "H";
		cout << setw(5) << "second " << clock << endl;
		cout << "HARE wins,YUCH";
		cout << endl;
	}
	if (pos_T >= 70 && pos_H >= 70)
	{
		for (int i = 0;i < 70;i++)
			cout << " ";
		cout << setw(5) << "sencond " << clock << endl;
		cout << "It's a tie!" << endl;
	}
	system("pause");
	return 0;



}
