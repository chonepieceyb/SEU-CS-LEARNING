#include<iostream>;
using namespace std;
int main()
{
	int a[] = { 1,3,5,7,9 };
	int* p[] = { a,a + 1,a + 2,a + 3,a + 4 };//指针数组，p也是一个数组名字
	int *p1 = a;
	int* p2 = a;
	cout << "Text 1:---------------------" << endl;
	cout << a[4] << "\t" << *(a + 2) << "\t" << *p[1] << "\t" << **(p + 1) << "\t" << **(p + 1) + a[2] << "\t"
		<< *(p + 4) - *(p + 0) << "\t" << *(a + 3) % a[4] << endl; //*(p+4)-*(p+0)z是指针算数 a+4-(a+0)
	cout << "Text 2------------------------" << endl;
	cout << *(++p1) << "\t" << *(p1+2) << "\t" << *(++++p1) << "\t" << endl;//????为什么*（++p1)的值为7 ,因为自增符号的优先级比较大所以先进行自增运算再进行流输出
	cout << "Text 3------------------------" << endl;
	cout << sizeof(p1) << "\t" << sizeof(*p1) << "\t" << &p1 << "\t" << *p1 << endl;
	system("pause");
	return 0;
}