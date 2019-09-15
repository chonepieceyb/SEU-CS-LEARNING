#include<iostream>
using namespace std;
int main()
{
	int total = 0,Num_Value = 0;
	int Num_counter ;
	cout << "Enter integers(first integer should be the number of subsequent integers)" << endl;
	cin >> Num_counter;
	for (int i=0;i<Num_counter;i++)
	{
		cin >> Num_Value;
		total = total+ Num_Value;
		
	}
	if(Num_counter!=0)
		cout << "\nThe average is " << static_cast<double>(total) / Num_counter << endl;
	else
		cout << "\nNo values were entered." << endl;
	system("pause");
	return 0;

}