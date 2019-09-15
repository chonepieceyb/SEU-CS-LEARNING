#include<iostream>
using namespace std;
int main()
{
	const int SIZE = 1000;
	int Prime_Array[SIZE];
	for (int i = 0;i < SIZE;i++)
		Prime_Array[i] = 1;
	int primecount = 2;
	while ( primecount < SIZE)
	{
		if (Prime_Array[primecount] == 1)
		{
			for (int i = 2;i*primecount < SIZE;i++)
			{
					Prime_Array[i*primecount] = 0;
			}
		}
		primecount++;
	}
	for (int i = 2;i < SIZE;i++)
	{ 
		if (Prime_Array[i] == 1)
			cout << i << "\t";
	}
		
	system("pause");
	return 0;
}