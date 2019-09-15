#include<iostream>
using namespace std;
int main()
{
	int BinNum;
	cout << "Please enter a binary integer ";
	cin >> BinNum;
	int temp = BinNum;
	int Num_Array[20];
	int i = 0;
	while (temp != 0)
	{
		Num_Array[i] = temp % 10;
		temp = temp / 10;
		i++;
	}
	i -= 1;
	int EquiNum=0;
	for (i;i >= 0;i--)
	{
		EquiNum = EquiNum * 2 + Num_Array[i];
	}
	cout << EquiNum;
	system("pause");
	return 0;
}