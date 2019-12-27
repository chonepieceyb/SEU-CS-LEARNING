#include "State.h"



State::State(int id)
{
	stateID = id;     //  -1 表示无效状态
	edgeJudgeFunction = nullptr; //为空
}


State::~State()
{
}

bool State::addPtrs(string c, State* next)        //增加某条边
{
	if (next_ptrs.find(c) == next_ptrs.end())
	{
		next_ptrs.insert({ c, next });
		return true;                            //如果存在边的话返回true
	}
	else {
		return false;                       
	}
}

bool State::removePtrs(string c)                // 移除某条边
{	
	auto iter = next_ptrs.find(c);
	if (iter != next_ptrs.end())
	{
		next_ptrs.erase(iter);
		return true;                            //如果存在边的话返回true
	}
	else {
		return false;
	}
}
State* State::transfer(string c)            //根据输入的字符返回下一个状态的指针
{   
	string key = c;
	if (edgeJudgeFunction != nullptr) {
		key = edgeJudgeFunction(c);
	}
	auto iter = next_ptrs.find(key);
	if (iter != next_ptrs.end())
	{
		return (*iter).second;                        //如果存在边的话返回指针
	}
	else {
		return nullptr;
	}
}

void State::setEdgeJudgeFunction(string(*f)(string str)) {
	edgeJudgeFunction = f;
}