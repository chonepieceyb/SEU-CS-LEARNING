#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int count = 0;
	long int hypotenuseSquared;
	long int sidetenuseSquared;
	long int loopcount = 0;
	cout << setw(5) << "Side1" << setw(5) << "Side2" << setw(5) << "Side3"<<endl;
	for (int side1 = 1;side1 <= 500;side1++)
	{
		if (side1 == 8)
			continue;
		for (int side2 = side1;side2 <= 500;side2++)
		{
			for (int side3 = side2+1; side3 <= 500 &&side3<side1+side2 ; side3++)  //三角形两边之和大于第三边
			{
				sidetenuseSquared = side1*side1 +side2*side2;
				hypotenuseSquared = side3*side3;
				if (sidetenuseSquared == hypotenuseSquared)
				{
					cout << setw(5) << side1 << setw(5) << side2 << setw(5) << side3 << endl;
					count++;
				}
				loopcount++;
				
			}
			
		}
		
	}
	cout << "A total of " << count << " triples were found." << endl;
	cout << "loopcount is " << loopcount;
    system("pause");
	return 0;

}