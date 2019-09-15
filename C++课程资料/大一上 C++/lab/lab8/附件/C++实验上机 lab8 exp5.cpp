#include<iostream>
using namespace std;
int strlen_my(const char* str)
{
	int pos = 0;
	int length = 0;
	while (str[pos] != '\0')
	{
		++length;
		pos++;
	}
	return length;
}                            //the function is like the strlen function in cstring header
char* strcop(char* s1, const char* s2)
{
	int pos = 0;
	while (s1[pos] != '\0'&& s2[pos] != '\0')
	{
		s1[pos] = s2[pos];
		pos++;
	}
	if (s2[pos] == '\0')
		s1[pos] = '\0';
	return s1;
}
int main()
{
	char s2[] = " I love my world and I love C++";
	char*s1;
	s1 = new char[strlen_my(s2)+1];
	cout << strcop(s1, s2);
	system("pause");
	return 0;
}
