#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int main()
{
	int Sequence[10];
	cout << "10 numbers as follow" << endl;
	srand(time(0));
	for (int i = 0;i<10;i++)
	{
		Sequence[i] = 1 + rand() % 300;
	}
	for (int i = 0;i<10;i++)
		cout << Sequence[i] << " ";
	cout << endl;
	int flag = 1;
	int SIZE = 9;
	while (flag == 1)
	{
		flag = 0;
		int swap;
		for (int i = 0;i<SIZE;i++)
		{
			if (Sequence[i]>Sequence[i + 1])
			{
				swap = Sequence[i + 1];
				Sequence[i + 1] = Sequence[i];
				Sequence[i] = swap;
				flag = 1;
			}
		}
		if (flag == 0)
			cout << "flag= " << flag << "The comparation stop! when SIZE= " << SIZE << endl;
		SIZE--;
	}
	for (int i = 0;i<10;i++)
		cout << Sequence[i] << " ";
	system("pause");
	return 0;
}