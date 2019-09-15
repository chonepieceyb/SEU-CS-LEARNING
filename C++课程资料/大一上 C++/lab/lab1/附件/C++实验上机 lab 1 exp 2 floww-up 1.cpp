#include<iostream>
using namespace std;

int main()
{
	int a[3], largest, smallest;
	std::cout << "Please input the first unmbers:";
	cin >> a[0];
	std::cout << "Please input the second unmbers:";
	cin >> a[1];
	std::cout << "Please input the third unmbers:";
	cin >> a[2];
	std::cout << "\nThe sum is:" << a[0] + a[1] + a[2];
	std::cout << "\nThe average is:" << (a[0] + a[1] + a[2]) / 3;
	std::cout << "\nThe product is:" << a[0] * a[1] * a[2];
	largest = a[0];
	for (int i = 0;i<3;i++)
	{
		if (largest<a[i])
			largest = a[i];
	};
	smallest = a[0];
	for (int i = 0;i<3;i++)
	{
		if (smallest>a[i])
			smallest = a[i];
	};

	std::cout << "\nThe largest number is:" << largest << "\nThe samllest number is:" << smallest << endl;
	getchar();
	getchar();
	return 0;
}