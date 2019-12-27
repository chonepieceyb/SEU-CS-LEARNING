#pragma once
#include<unordered_map>

using namespace std;

// 这里的State是DFA的State
class State
{
public:
	State(int id);
	~State();
	// getter
	inline int getStateID() {
		return stateID;
	}
	bool addPtrs(const string c, State* next);        //增加某条边
	bool removePtrs(const string c);                 // 移除某条边
	void setEdgeJudgeFunction(string(*f)(string str));
	State* transfer(const string c);                //根据输入的字符返回下一个状态的指针
protected:
	unordered_map<string, State*> next_ptrs ;
	string (*edgeJudgeFunction) (string str);
	int stateID;
};

