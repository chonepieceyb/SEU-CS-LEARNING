#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	const int SIZE = 10;
	int Sequence[SIZE];
	cout << "10 numbers as follow" << endl;
	srand(time(0));
	for (int i = 0;i<SIZE;i++)
	{
		Sequence[i] = 1 + rand() % 300;
	}
	for (int i = 0;i<10;i++)
		cout << Sequence[i] << " ";
	cout << endl;
		int swap;
		for (int j = 0;j<SIZE - 1;j++)
		{ 
			for (int i = 0;i<SIZE - 1;i++)
			{
				if (Sequence[i]>Sequence[i + 1])
				{
					swap = Sequence[i + 1];
					Sequence[i + 1] = Sequence[i];
					Sequence[i] = swap;
				}
			}
		}
			
	for (int i = 0;i<10;i++)
		cout << Sequence[i] << " ";
	system("pause");
	return 0;
}