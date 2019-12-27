#pragma once
#include "ParserState.h"
#include"ProductionManager.h"
class LR1State :
	public ParserState
{
public:
	LR1State(int state_ID);
	~LR1State();
	virtual bool operator==(const ParserState& p)const;                 //必须要重载一个==函数
	virtual bool operator<(const ParserState& p)const;
	virtual void calFollowSet(ProductionStack& p, set<ProductionStack>& fps);          //计算状态内的一个表达式的follow集合
	virtual void stateGrow(ProductionManager& pm);
};

