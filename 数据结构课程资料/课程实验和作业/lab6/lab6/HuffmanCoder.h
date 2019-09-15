#ifndef HUFFMANCODER_H
#define HUFFMANCODER_H
#include"HuffmanTree.hpp"
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
class HuffmanCoder
{
public:
	HuffmanCoder(int n=26);
	~HuffmanCoder();
	bool creatHuffmanTree(ifstream& fin); //从文件中读入数据并做出统计,然后做出一棵哈夫曼树
	bool creatCode(ifstream& fin, ofstream& fout);  //从文件中读入字符，输出编码
	bool translateCode(ifstream& fin, ofstream& fout); //从文件中读入编码，并且翻译
    bool compare(ifstream& finOrigin, ifstream& finTargt); //比较源码和译码
	void makeEmpty(); //重置
	void outputWeight();
	void outputCode();
private:
	HuffmanTree<double>* huffmanPtr;
	double * weight;
	int nums;

};

#endif


