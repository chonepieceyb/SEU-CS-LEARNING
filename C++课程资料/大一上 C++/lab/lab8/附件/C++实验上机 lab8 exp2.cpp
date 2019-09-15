#include<iostream>
using namespace std;
int main()
{
	const int size = 10;
	int array1[size] = { 1,7,11,56,-200,95,0,-6,42,17 };
	int* pos = new int;
	for (int i = 0;i<size;i++) //ัก9ดฮ
	{
		for (int j = i;j<size;j++)
		{
			if (*(array1 + i)>*(array1 + j))
			{
				*pos = *(array1 + j);
				*(array1 + j) = *(array1 + i);  //swap
				*(array1 + i) = *pos;
			}
		}
	}
	for (int i = 0;i<size;i++)
	{
		cout << *(array1 + i) << endl;
	}
	system("pause");
	return 0;
}