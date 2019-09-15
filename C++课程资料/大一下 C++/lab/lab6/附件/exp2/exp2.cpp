#include<iostream>
#include"Array.h"
#include<string>
using namespace std;
int main()
{
	Array<5, int> array1;
	cout << "Enter 5 integers \n";
	cin >> array1;
	cout << array1;
	cout << endl;
	Array<5, string> array2;
	cout << "Enter 5 strings \n";
	for (int i = 0;i < array2.size();i++)
		cin >> array2[i];
	for (int i = 0;i < array2.size();i++)
		cout << array2[i] << " ";
	cout << endl;
	system("pause");
	return 0;
}