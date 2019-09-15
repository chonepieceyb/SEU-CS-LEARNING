#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
void TOTALARRAY(int CounterArray[][6])     //A function to produce the total value of two faces 
{

	int first;
	int second;
	first = 1 + rand() % 6;
	second = 1 + rand() % 6;
	++CounterArray[first - 1][second - 1];
}
int main()
{
	const int ROLLS = 36000;
	const int SIZE = 13;
	int CounterArray[6][6] = { 0 };
	srand(time(0));
	for (int i = 0;i<36000;i++)
	{
		TOTALARRAY(CounterArray);

	}
	cout << fixed << setprecision(3) << fixed << showpoint;
	for (int i = 1;i <= 6;i++)
		cout << setw(10) << i;
	cout << endl;
	for (int i = 0;i<6;i++)
	{
		cout << i;
		for (int j = 0;j<6;j++)
		{
			cout << setw(10) << CounterArray[i][j];

		}
		cout << endl;
	}
	system("pause");
	return 0;

}




		
		     





