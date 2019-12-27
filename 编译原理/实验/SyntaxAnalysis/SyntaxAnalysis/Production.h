#pragma once
#include"NonTerminator.h"
#include<iostream>
#include<fstream>
using namespace std;
class Production
{
	
	/*
	产生式类，包含一个指向非终结符的指针，和一个该终结符下的产生式id
	*/
public:
	Production(NonTerminator* head,int production_id);
	set<string> getFirstSet();
	virtual void printProduction()const;
	virtual void outputProductionAsFile(ofstream& fout)const;
	int getProductionSize()const;
	ATTRIBUTE_READ_ONLY(NonTerminator*, head);
	ATTRIBUTE_READ_ONLY(int, production_id);
	~Production();
protected:
	NonTerminator* head;      //产生式的头部，就是非终结符的指针
	int production_id;        //该终结符下的第几个产生式    

};

