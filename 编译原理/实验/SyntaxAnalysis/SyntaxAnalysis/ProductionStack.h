#pragma once
#include "Production.h"
class ProductionStack :
	public Production
{
	/*
	这个类是 在LR(1)文法中的，产生式，包含 follow集合（是LR(1)意义上的follow集合）
	以及当前stack的状态（就是小点点）
	还有一个标记是该式子是否被访问过了
	*/
public:
	ProductionStack(NonTerminator* head, int production_id);
	void stateInit();
	virtual bool operator==(const ProductionStack& p)const;    //允许重载
	virtual bool operator<(const ProductionStack& p)const;
	virtual bool operator>(const ProductionStack& p)const;
	virtual void printProduction()const;
	virtual void outputProductionAsFile(ofstream& fout)const;
	virtual bool isProductionEuqal(ProductionStack& p);   //判断表达式（只判断产生式子）是否相同
	bool insertFollowSets(set<string> set);
	bool insertFollowSet(string set);
	//set 和get函数
	ATTRIBUTE_MEMBER_FUNC(int, stackState); 
	ATTRIBUTE_MEMBER_FUNC(bool, isProcess);
	ATTRIBUTE_MEMBER_FUNC(set<string>, followSet);
	~ProductionStack();
private:
	int stackState;
	set<string> followSet;       //LR(1)文法中的follow集合
	bool isProcess;                      
};

