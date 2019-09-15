#include<iostream>
using namespace std;
using namespace std;
void square(char, int);
void diamond(char, int);//º¯ÊýÉùÃ÷
void triangle(char, int);
void square(char character, int size)
{
	for (int i = 0;i< size; i++)
	{
		for (int i = 0;i<size;i++)
			cout << character;
		cout << endl;
	}
	return;
}
void diamond(char character, int size)
{
	int lines = (size + 1) / 2;
	int i;
	for (i = 1;i <= lines;i++)
	{
		for (int j = 0;j<(size - (i * 2 - 1)) / 2;j++)
			cout << " ";
		for (int j = (size - (i * 2 - 1)) / 2;j<(size - (size - (i * 2 - 1)) / 2);j++)
			cout << character;
		for (int j = (size - (size - (i * 2 - 1)) / 2);j<size;j++)
			cout << " ";
		cout << endl;
	}
	i -= 2;
	for (i;i>0;i--)
	{
		for (int j = 0;j<(size - (i * 2 - 1)) / 2;j++)
			cout << " ";
		for (int j = (size - (i * 2 - 1)) / 2;j<(size - (size - (i * 2 - 1)) / 2);j++)
			cout << character;
		for (int j = (size - (size - (i * 2 - 1)) / 2);j<size;j++)
			cout << " ";
		cout << endl;
	}
	return;
}
void triangle(char character, int size)
{
	int lines = size;
	int i;
	for (i = 1;i <= lines;i++)
	{
		for (int j = 0;j<((2 * size - 1) - (i * 2 - 1)) / 2;j++)
			cout << " ";
		for (int j = ((2 * size - 1) - (i * 2 - 1)) / 2;j<((2 * size - 1) - ((2 * size - 1) - (i * 2 - 1)) / 2);j++)
			cout << character;
		for (int j = ((2 * size - 1) - ((2 * size - 1) - (i * 2 - 1)) / 2);j<size;j++)
			cout << " ";
		cout << endl;
	}
	return;
}
int main()
{
	char character;int size, type, flag;
	do
	{
		cout << "Choose the shape to graph\n" << "1 for square\n" << "2 for diamond\n" << "3 for triangle\n";
		cout << "?";
		cin >> type;
		cout << "\nEnter a character and size:";
		cin >> character >> size;
		switch (type)
		{
		case 1: square(character, size);break;
		case 2: diamond(character, size);break;
		case 3: triangle(character, size);break;
		}
		cout << endl << endl << "Do you want to continue?(y or n£©";
		char x;
		cin >> x;
		if (x == 'y');
		flag = 1;
		if (x == 'n')
		{
			flag = 0;break;
		}
	} while (flag == 1);
	system("pause");
	return 0;
}