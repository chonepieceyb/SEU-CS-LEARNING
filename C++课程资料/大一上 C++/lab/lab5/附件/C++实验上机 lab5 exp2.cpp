#include<iostream>;
using namespace std;
bool perfect(int number)
{
	int total = 1; //1肯定是任何数的因子
	for (int p = 2;p<number;p++) //p<number 不包括这个数本身
	{
		if (number%p == 0)
		{
			total = total + p;
		}
	}
	if (total == number)
		return true;

	else
		return false;
}
int main()
{
	int small, large;
	cout << "Perfect integers between ";
	cin >> small;
	cout << "and ";
	cin >> large;
	cout << endl;
	for (int i = small;i <= large;i++)
	{
		if (perfect(i))
		{
			if (i != 1)
			{
				cout << i << "= 1";
				for (int p = 2;p<i;p++)
				{
					if (i%p == 0)
						cout << "+" << p;
				}
				cout << endl;
			}
		}
	}
	system("pause");
	return 0;

}