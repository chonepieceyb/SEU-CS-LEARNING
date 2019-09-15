#include<iostream>
using namespace std;
int main()
{
	int number_five;
	cout << "请输入一个五位数；  ";
	cin >> number_five;
	int temp_five= number_five;
	cout << temp_five % 10<<" ";
	temp_five = temp_five / 10;
	cout << temp_five % 10 << " ";
	temp_five = temp_five / 10;
	cout << temp_five % 10 << " ";
	temp_five = temp_five / 10;
	cout << temp_five % 10 << " ";
	temp_five = temp_five / 10;
	cout << temp_five % 10 << " ";
	temp_five = temp_five / 10;
	system("pause");
	return 0;
	
	

}