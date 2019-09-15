#include<iostream>
#include<cstring>
using namespace std;


char* strcat_my(char* s1, const char* s2)
{
	int posS1 = strlen(s1);
	int posS2 = 0;
	do
	{
		s1[posS1] = s2[posS2];
		posS1++;
		posS2++;
	} while (s2[posS2] != '\0');
	if (posS2 == '\0');   //×Ô¼º²¹ÉÏ'\0'
	s1[posS1] = '\0';

	return s1;
}
int main()
{
	char s1[40] = "I love the world";
	char* s2 = "I love C++    ";
	cout << "The result is " << endl << strcat_my(s1, s2);
	system("pause");
	return 0;
}
