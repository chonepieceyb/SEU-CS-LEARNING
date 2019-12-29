#include "DFA.h"



DFA::DFA()
{
}


DFA::~DFA()
{
}

bool DFA :: addTokenItem(int key, tokenItem i) {
	if (tokenDict.find(key) == tokenDict.end())
	{
		tokenDict.insert({ key, i });
		return true;                            //如果存在边的话返回true
	}
	else {
		return false;
	}
}
bool DFA::addTokenItem(int key, int token_id, string token_name) {
	tokenItem i = tokenItem(token_id, token_name);
	if (tokenDict.find(key) == tokenDict.end())
	{
		tokenDict.insert({ key, i });
		return true;                            //如果存在边的话返回true
	}
	else {
		return false;
	}
}
bool DFA :: removeTokenItem(int key, tokenItem i) {
	auto iter = tokenDict.find(key);
	if (iter != tokenDict.end())
	{
		tokenDict.erase(iter);
		return true;                            //如果存在边的话返回true
	}
	else {
		return false;
	}
}
bool  DFA::addKeepWord(string keyword, int token_id) {
	auto iter = keepWords.find(keyword);
	if (iter == keepWords.end())
	{
		token t =  token(token_id, keyword, "_");      //关键词的token没有值
		keepWords.insert({ keyword,t });
		return true;
	}
	else {
		return false;
	}
}
void DFA::addState(State s)                     //添加状态
{
	states.push_back(s);
}
void  DFA::initStates(const int stateNum,  vector<int>** stateMatrix, const string edgeList[]) {
    //初始化state
	// stateMatrix 矩阵 ，其中 从状态 i -> j 的边 的值为 edgeList[i][j]<<
	for (int i = 0; i < stateNum;  i++) {
		states.push_back(State(i));
	}
	for (int i = 0; i < stateNum; i++) {
		for (int j = 0; j < stateNum; j++) {
			vector<int> v = *(*(stateMatrix + i) + j);
			//vector<int> v = stateMatrix[i][j];
			if (v.size()<=0) {
				continue;                     // edge vector里没有数据
			}
			else {
				for (int p = 0; int(p < v.size()); p++) {
					states[i].addPtrs(edgeList[v[p]], &states[j]);
				}
			}
		}
	}
}
State& DFA::getState(int i) {
	return (states[i]);
}
token DFA::isKeepWord(string keyword) {
	auto iter = keepWords.find(keyword);
	if (iter != keepWords.end())
	{
		return (*iter).second;
	}
	else {
	    token t = token(-1, "no key word", "_");
		return t;
	}
}
token DFA::scan(string str, string(*inputConvert)(char c)) {
	// 扫描字符串，字符串的结尾必须是结束符 end, DFA的 states 0 是初始状态,第二个参数是一个函数指针，指向一个将字符映射为字符串边的函数，默认将字符直接转化为string
    // 先判断是不是关键字
	token  t = isKeepWord(str);
	if (t.getTokenID() != -1) {
		return t;
	}
	State* state = &(states[0]);   // 获得初始状态的指针
	int index = 0;
	while (state != nullptr) {
		char c = str[index];
		string ch = inputConvert(c);
		if (index>=int(str.length())) {
			//如果是终结符
			int key = state->getStateID();
			auto iter = tokenDict.find(key);     //查找
			if (iter != tokenDict.end()) {
				//如果找到了
				tokenItem ti = (*iter).second;
				token t = token(ti.token_id, ti.token_name, str);
				return t;
			}
			else {
				cout << "lexical_error\n";    //词法错误
				token t = token(-1, "lexical_error", str);
				cout << t << endl;
				return t;
			}
		}
		//如果不是终结符，查找下一个状态
		state = state->transfer(ch);
		if (state == nullptr) {
			//如果找不到的话，报错
			cout << "lexical_error\n";
			str.pop_back();
			token t = token(-1, "lexical_error", str);
			cout << t << endl;
			return t;
		}
		index++;     //读取下一个字符
	}
	
}