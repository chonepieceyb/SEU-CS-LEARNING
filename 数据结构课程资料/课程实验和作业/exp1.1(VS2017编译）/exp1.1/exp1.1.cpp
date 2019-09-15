#include<iostream>
#include<ctime>
using namespace std;
long int Inequality(long int n, long  int& count, long int &pos)
{

	long int tempCount = 0;
	long int total = 0;
	long int i = 1;

	tempCount += 3;
	while (total < n)
	{
		tempCount += 1;
		total += i;
		i++;
		tempCount += 2;
	}
	tempCount += 1;
	count = tempCount;
	pos = i - 2;
	return i;
}

int main()
{

	long  int n;
	char flag = 'n';
	long int count, i = 0;
	double duration;
	clock_t start=0, stop=0;

	do {
		cout << "请输入一个数字n" << endl;
		cin >> n;
		 start = clock();
		Inequality(n, count, i);
		 stop = clock();
		duration = (static_cast<double>(stop - start)) / CLK_TCK;
		cout << "满足不等式i的最小值" << i << endl;
		cout << "算法(只计算函数执行的程序步）的程序步骤" << count << endl;
		cout << "算法执行的时间" << duration << endl;
		cout << endl;
		cout << "输入n退出" << endl;
		cin >> flag;
	} while (flag != 'n');
	system("pause");
	return 0;
}