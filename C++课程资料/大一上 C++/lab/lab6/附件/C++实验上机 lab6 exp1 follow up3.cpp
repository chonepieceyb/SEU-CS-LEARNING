#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
int TOTAL()     //A function to produce the total value of two faces 
{

	int first;
	int second;
	first = 1 + rand() % 6;
	second = 1 + rand() % 6;
	int total = first + second;
	return total;
}
int main()
{
	const int ROLLS = 36000;
	const int SIZE = 13;
 int counter[13];
	srand(time(0));
	float expected[13] = { 0,0,2.778,5.556,8.333,11.111,13.889,16.667,13.889,11.111,8.333,5.556,2.778, };
	for (int i = 0;i<36000;i++)
	{

		++counter[TOTAL()];
	}
	cout << fixed << setprecision(3) << fixed << showpoint;
	cout << setw(10) << "Sum" << setw(10) << "Total" << setw(10) << "Expected" << setw(10) << "Actual" << endl;
	for (int i = 2;i < SIZE;i++)
	{
		cout << setw(10) << i << setw(10) << counter[i] << setw(10) << expected[i] << "%" << setw(10) << (static_cast<float>(counter[i])) * 100 / 36000 << "%" << endl;
	}
	system("pause");
	return 0;
}


