#include<iostream>
#include<iomanip>
using namespace std;
int tripleByValue(int);
void tripleByRefrence(int &);
int main()
{
	int count = 4;
	cout << "It's now pass by value" << endl;
	cout << tripleByValue(count) << endl;
	count = 4;
	cout << "The value of count has been reseted as 4" << endl;
	tripleByRefrence(count);
	cout << "	The value of count is: " << count << " now!";
	getchar();
	return 0;
}
int tripleByValue(int count)
{
	return 3 * count;
}

void tripleByRefrence(int & count)
{
	count *= 3;
}