#pragma once
#include<vector>
#include "State.h"
#include<string>
#include<unordered_map>
#include<vector>
#include "token.h"
#include<iostream>
using namespace std;
class DFA
{
	struct tokenItem{      //该结构体是 token的 id 和 name对应的一个结构体
		int token_id;
		string token_name;
		tokenItem(int t_id, string t_name):token_id(t_id),token_name(t_name) {
		}
	};
public:
	DFA();
	~DFA();
	bool addTokenItem(int key, tokenItem i);
	bool addTokenItem(int key, int token_id, string token_name);
	bool removeTokenItem(int key, tokenItem i);     
	bool addKeepWord(string keyword,int token_id);
	void addState(State s);                          //添加状态
	State& getState(int i);
	void initStates(const int stateNum,  vector<int>** stateMatrix, const string edgeList[]);
	token isKeepWord(string keyword);                       //判断是不是保留字
	token scan(string str,  string(*inputConvert)(char c) = [](char c)->string {return string(1, c); });// 扫描字符串生成token
private:
	string end;
	unordered_map<int, tokenItem> tokenDict;       // 终结符
	unordered_map<string, token> keepWords;        // 保留字
	vector<State> states;
};
