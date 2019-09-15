#ifndef ITEM_H
#define ITEM_H
#include<stdexcept>
#include<iostream>
using namespace std;
class Item
{
private:
	int x;
public:
	Item(int t)
	{
		    if (t != 3)
			{
				x = t;
				cout << "The constructor of Item" << x << " is called\n";
			}
			else
			{
				cout << "The constructor of Item\n";
				throw runtime_error("An exception is thrown");
				cout<< x << " is called\n";
			}
		
	}
	~Item()
	{
		cout << "The destructor of Item" << x << " is called\n";
	}
};
#endif // !ITEM_H

