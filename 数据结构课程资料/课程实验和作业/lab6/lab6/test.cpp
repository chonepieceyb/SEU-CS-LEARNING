#include"HuffmanTree.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include"HuffmanCoder.h"
using namespace std;
int main()
{
	ifstream fin;
	fin.open("English.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}
	ifstream fin1;
	fin1.open("English.txt", ios::in);
	if (!fin1.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}

	ofstream fout;
	fout.open("code.txt", ios::out);
	if (!fout.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}
	
	cout << "开始哈夫曼编码,对根目录下的english.txt进行编码" << endl;
	HuffmanCoder coder(26);
	if (coder.creatHuffmanTree(fin) && coder.creatCode(fin1, fout))
		cout << "编码成功，编码文件在根目录下的code.txt" << endl;
	else
		cout << "编码失败！" << endl;
	
	fin.close();
	fin1.close();
	fout.close();
	ifstream fin2;
	fin2.open("code.txt", ios::in);
	if (!fin2.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}
	ofstream fout1;
	fout1.open("uncode.txt", ios::out);
	if (!fout1.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}
	cout << "开始解码" << endl;
	if (coder.translateCode(fin2, fout1))
		cout << "解码成功，解码文件在根目录下的uncode.txt" << endl;
	else
		cout << "解码失败" << endl;
	fin2.close();
	fout1.close();
	cout << "开始输出哈夫曼树的总权值" << endl;
	coder.outputWeight();

	cout << "开始输出各个字符对应的前缀码" << endl;
	coder.outputCode();
	//输出权值
	cout << "\n开始比较文本" << endl;
	ifstream finOrigin;
	finOrigin.open("English.txt", ios::in);
	if (!finOrigin.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}

	ifstream finTarget;
	finTarget.open("uncode.txt", ios::in);
	if (!finTarget.is_open())
	{
		cout << "打开文件失败！" << endl;
		return 0;
	}
	if (coder.compare(finOrigin, finTarget))
		cout << "文本比较无误" << endl;
	else
		cout << "文本比较出现错误" << endl;
	finOrigin.close();
	finTarget.close();
	system("pause");
	return 0;
}