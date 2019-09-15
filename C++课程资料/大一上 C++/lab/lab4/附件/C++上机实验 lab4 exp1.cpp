#include<iostream>
using namespace std;
int main()
{
	int total = 0,Num_Value = 0;
	int Num_counter = 0;
	cout << "Enter integers £¨9999£©to ends" << endl;
	cin >> Num_Value;
	for (;Num_Value != 9999;)
	{
		total = total + Num_Value;
		Num_counter++; 
		cin >> Num_Value;
	}
	if(Num_counter!=0)
		cout << "\nThe average is " << static_cast<double>(total) / Num_counter << endl;
	else
		cout << "\nNo values were entered." << endl;
	system("pause");
	return 0;

}