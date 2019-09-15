#include<iostream>
using namespace std;
int main()
{
	const int size_R = 3;
	const int size_C = 5;
	int array_my[size_R][size_C] = {
		{ 1,2,3,4,5 },
		{ 6,7,8,9,10 },
		{ 10,11,12,13,14 }
	};
	for (int i = 0;i < size_R;i++)
	{
		for (int j = 0;j < size_C;j++)
			cout << *(*(array_my + i) + j) << ' ';
		cout << endl;
	}
	system("pause");
	return 0;
}
