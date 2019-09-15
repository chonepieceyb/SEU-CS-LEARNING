#include<iostream>
#include"Shape.h"
#include"Square.h"
#include"Cube.h"
#include"TwoDimensionalShape.h"
#include<vector>
using namespace std;
int main()
{
	vector<Shape*> shapes;
	Square a(4.5, 3);
	Cube b(0.5, 2, 7.9);
	shapes.push_back(&a);
	shapes.push_back(&b);
	shapes[0]->print();
	cout << endl;
	shapes[1]->print();
	return 0;
}
