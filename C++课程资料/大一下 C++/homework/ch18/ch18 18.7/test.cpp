#include<iostream>
#include<fstream>
#include<string>
#include"Encrypter.h"
#include"Decrypter.h"
using namespace std;
int main()
{
	string Key;
	ifstream fin("D:\\some date and files\\C++上机 2\\作业\\ch18\\ch18 18.7\\original.txt", ios::in);
	if (!fin)
	{
		cout << "Fail to open the original file";
		exit(1);
		return 0;
	}
	getline(fin, Key);   //用于输入句子
	fin.close();
	ofstream fout1("D:\\some date and files\\C++上机 2\\作业\\ch18\\ch18 18.7\\Encrypts.txt", ios::out);
	if (!fout1)
	{
		cout << "Fail to open the original file";
		exit(1);
		return 0;
	}
	Encrypter encryper(13);
	encryper.encrypt(Key);
	fout1 << Key;
	fout1.close();
	ofstream fout2("D:\\some date and files\\C++上机 2\\作业\\ch18\\ch18 18.7\\Decryptes.txt", ios::out);
	if (!fout2)
	{
		cout << "Fail to open the original file";
		exit(1);
		return 0;
	}
	Decrypter decrypter(encryper);
	decrypter.Decrypts(Key);
	fout2 << Key;
	fout2.close();
	return 0;
}