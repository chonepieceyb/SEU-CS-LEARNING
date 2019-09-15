#include"HuffmanCoder.h"
HuffmanCoder::HuffmanCoder(int n):nums(n)
{
	huffmanPtr = nullptr;
	weight = nullptr;
}
HuffmanCoder::~HuffmanCoder()
{
	if (huffmanPtr != nullptr)
	{
		delete huffmanPtr;
		huffmanPtr = nullptr;

	}
	if (weight != nullptr)
	{
		delete[] weight;
		weight = nullptr;

	}
}
bool HuffmanCoder::creatHuffmanTree(ifstream& fin) //从文件中读入数据并做出统计,然后做出一棵哈夫曼树
{
	if (huffmanPtr != nullptr)
	{
		cout << "已经构建过哈夫曼树了，无法继续构建" << endl;
		return false;
	}
	//构建一个临时数组用来放26个字母（不区分大小写）
	char* dictionary=new char[nums];
	if (dictionary == nullptr)
	{
		cerr << "无法分配空间";
		exit(1);
	}
	for (int i = 0; i < nums; i++)  //初始化
	{
		dictionary[i] = 'a' + i;
	}
	//开始进行统计
	int total = 0; //总数目
    weight = new double[nums]; //权值矩阵
	if (weight == nullptr)
	{
		cerr << "无法分配空间";
		exit(1);
	}
	for (int i = 0; i < nums; i++)
	{
		weight[i] = 0;
	}
	char x=0; 
	while (fin >> x)  //如果不是读到文件结尾的话
	{

		if (x >= 'a'&& x <= 'z')  //如果是小写的
		{
			//目前只是统计数目
			weight[x - 'a']++;
			total++;
		}
		else if (x >= 'A'&& x <= 'Z')  //如果是大写字母
		{
			//目前只是统计数目

			weight[x - 'A']++;
			total++;
		}
		else  //如果都不是的话跳过
		{
			;
		}

	}
	//计算权值
	/*for (int i = 0; i < nums; i++)
	{
		weight[i] = weight[i] / total;
	}*/
	//构建哈夫曼树
	huffmanPtr = new HuffmanTree<double>(weight, dictionary, nums);
	//回收空间
	delete[]dictionary;
	return true;
}
bool HuffmanCoder::creatCode(ifstream& fin, ofstream& fout)  //从文件中读入字符，输出编码
{
	if (huffmanPtr == nullptr)
	{
		cout << "还未构建哈夫曼树，无法编码" << endl;
		return false;
	}
	char x=0 ;
	string code;
	while (fin>> x)  //如果不是读到文件结尾的话
	{
		code = "";
		if (x >= 'a'&& x <= 'z')  //如果是小写的
		{
			huffmanPtr->findHuffmanCode(int(x - 'a'), code);
		}
		else if (x >= 'A'&& x <= 'Z')  //如果是大写字母
		{
			huffmanPtr->findHuffmanCode(int(x-'A'), code);
		}
		else  //如果都不是的话跳过
		{
				;
		}
		//输出编码

		fout << code;
	}
	return true;
}
bool  HuffmanCoder::translateCode(ifstream& fin, ofstream& fout)//从文件中读入编码，并且翻译
{
	if (huffmanPtr == nullptr)
	{
		cout << "还未构建哈夫曼树，无法译码" << endl;
		return false;
	}
	huffmanPtr->translateHuffmanCode(fin, fout);
	return true;
}
bool HuffmanCoder::compare(ifstream& finOrigin, ifstream& finTarget)//比较源码和译码
{
	char x=0, y=0;

	while (finOrigin >> x)  //如果不是读到文件结尾的话
	{
		if (x >= 'a'&& x <= 'z')  //如果是小写的
		{
			finTarget >> y;
			if (x != y)
				return false;

		}
		else if (x >= 'A'&& x <= 'Z')  //如果是大写字母
		{
			finTarget >> y;
			if (int(x - 'A') != int(y - 'a'))
				return false;
		
		}
		else  //如果都不是的话跳过
		{
			;
		}
	}
	//测试
	if (finTarget >> y)
		return false;
	else
		return true;

}
void HuffmanCoder::makeEmpty()
{
	if (weight != nullptr)
	{
		delete[] weight;
		weight = nullptr;

	}
	if (huffmanPtr != nullptr)
	{
		delete huffmanPtr;
		huffmanPtr = nullptr;
	}
}
void HuffmanCoder::outputWeight()
{
	if (weight == nullptr)
		return;
	for (int i = 0; i < nums; i++)
	{
		cout <<char( 'a' + i) << "的权值为: " << weight[i] << endl;
	}
	cout << "总权值之和为："; 
	huffmanPtr->outputWholeWeight();
	cout << endl;
}
void HuffmanCoder::outputCode()
{
	string code;
	for (int i = 0; i < nums; i++)
	{
		code = "";
		huffmanPtr->findHuffmanCode(i, code);
		cout << char('a' + i) << "的哈夫曼编码为： " << code<<endl;
	}
}