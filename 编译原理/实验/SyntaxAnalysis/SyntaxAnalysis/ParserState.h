#pragma once
#include"ProductionStack.h"
#include<unordered_map>
#include"ProductionManager.h"
#include<fstream>
class ParserState
{
public:
	ParserState(int state_ID);
	virtual ~ParserState();
	void init();
	virtual ParserState* transfer(string input);
	virtual void calFollowSet(ProductionStack& p, set<ProductionStack>& fps ) = 0;          //计算状态内的一个表达式的follow集合
	virtual void stateGrow(ProductionManager& pm) = 0;
	virtual bool operator==( const ParserState& p)const= 0;                 //必须要重载一个==函数
	virtual bool operator<(const ParserState& p)const=0;
	virtual void printState()const;
	virtual void outputStateAsFile(ofstream& fout)const;
	bool addNextState(string key, ParserState* s);
	bool addProduction(ProductionStack &p);                       //注意，这里采用了值传递，也就是说每隔state对象内部保存有独立的productionStack对象副本！！！可能会出错
	bool addProductionAsMerge(ProductionStack& p);               // 再强化一下C++的值传递和引用传递的区别特别是对于类来说
	const unordered_map<string, ParserState*>& getNextStates()const;
	static set<string> convertFirstSetToString(set<Node*>& firstset);
	ATTRIBUTE_READ_ONLY(set<ProductionStack>, productions);
	ATTRIBUTE_MEMBER_FUNC(int, stateID)
	ATTRIBUTE_MEMBER_FUNC(bool,isProcess)
protected:
	bool isProcess;
	int stateID;   //stateID >=0 有效， stateID = -1时，表示不错在该状态， stateID=-2是表示状态未分配id值
	set<ProductionStack> productions;                          //集合
	unordered_map<string, ParserState*> nextStates;

};

