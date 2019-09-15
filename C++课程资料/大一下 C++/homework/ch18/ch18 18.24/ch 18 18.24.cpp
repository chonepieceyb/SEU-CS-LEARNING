#include<iostream>
#include<iostream>
#include<string>
using namespace std;
const string standard("abcdefghijklmnopqrstuvwxyz");
string Round(string& a)
{
	string temp = a;
	if (a == "")
		return a;
	for (int i = 0;i < a.size() ;i++)
	{
		a[i] = temp[a.size()-i-1];
	}
	return a;
}
void printline(int t_iLine)
{
	if (t_iLine == 14)
	{
		string t_String(27, ' ');
		int t_iNum = t_iLine * 2 - 1;
		int t_ihalfNum = (27 - t_iNum) / 2;
		string print;
		print = standard.substr(t_iLine - 1, t_iNum / 2);
		string temp = print;
		print = print + "{" + Round(temp);
		t_String.replace(t_ihalfNum, t_iNum, print);
		cout << t_String << endl;
    }
	else
	{
		string t_String(27, ' ');
		int t_iNum = t_iLine * 2 - 1;
		int t_ihalfNum = (27 - t_iNum) / 2;
		string print;
		if (t_iLine != 1)
			print = standard.substr(t_iLine - 1, t_iNum / 2);
		else
			print = "";
		string temp = print;
		print =print+standard[t_iLine + t_iNum / 2 - 1]+Round(temp);
		t_String.replace(t_ihalfNum,t_iNum, print);
		cout << t_String << endl;
	}
}
int main()
{
	for (int i = 1;i <= 14;i += 1)
	{
		printline(i);
	}
	system("pause");
}
