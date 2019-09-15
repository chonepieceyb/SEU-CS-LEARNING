#include<iostream>
using std::cout;
using std::endl;
#include"IntegerSet.h"
int main()
{
	IntegerSet a;
	IntegerSet b;
	IntegerSet c;
	IntegerSet d;
	cout<<"Enter set A:\n";
	a.inputSet();
	cout<<"\nEnter set B:\n";
	b.inputSet();
	c=a.unionOfSets(b);
	d=a.intersectionOfSets(b);
	cout<<"\nUnion of A and B is:\n";
	c.printSet();
	cout<<"\nIntersection of A and B is:\n";
	d.printSet();
	if(a.isEqualTo(b))
		cout<<"Set A is equal to set B\n";
	else
		cout<<"Set A is not equal to set B\n";
	cout<<"\nInserting 77 from set A...\n";
	a.insertElement(77);
	cout<<"Set A is now:\n";
	a.printSet();
	cout<<"\nDeleting 77 from set A...\n";
	a.deleteElement(77);
	cout<<"Set A is now:\n";
	a.printSet();
	const int arraySize=10;
	int intArray[arraySize]={25,67,2,9,99,105,45,-5,100,1};
	IntegerSet e(intArray,arraySize);
	cout<<"\nSet e is";
	e.printSet();
	cout<<endl;
	system("pause");
	return 0;
}















