#include<iostream>
#include"Polynomial.h"
using namespace std;
int main()
{
	int a[5] = {1,0,-3,-4,5};
	int b[3] = { 2,3,2 };
	int c[2] = { 5,4 };
	Polynomial Plo1(a, 4);
	Polynomial Plo2(Plo1);
	cout << "Plo1:" << Plo1<<endl;
	cout << "Plo2:" << Plo2 << endl;
	cout << "Plo1+Plo2= " << Plo1 + Plo2<<endl;
	cout  << "After Plo1+=Plo2"<<endl;
	Plo1 += Plo2;
	cout << "Plo1:" << Plo1 << endl;
	cout << "Plo1-Plo2= " << Plo1 - Plo2 << endl;
	cout << "After Plo1-=Plo2" << endl;
	Plo1 -= Plo2;
	cout << "Plo1:" << Plo1;
	Polynomial Plo3(b, 2);
	Polynomial Plo4(c, 1);
	cout << "Plo3:" << Plo3 << endl;
	cout << "Plo4:" << Plo4 << endl;
	Polynomial Plo5 = Plo3*Plo4;
	cout << "Plo3*Plo4= "<< Plo3*Plo4 << endl;
	cout << "After Plo3*=Plo4" << endl;
	Plo3 *= Plo4;
	cout << "Plo3:" << Plo3 << endl;
	system("pause");
}