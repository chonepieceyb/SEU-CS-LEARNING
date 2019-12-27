#include "ParserState.h"



ParserState::ParserState(int state_ID):stateID(state_ID)
{
	//初始化
	init();
}
void ParserState::init() {
	//初始化
	productions = set<ProductionStack>();
	nextStates = unordered_map<string, ParserState*>();
	isProcess = false;
}
ParserState* ParserState::transfer(string input)
{
	auto iter = nextStates.find(input);
	if (iter != nextStates.end()) {
		return (*iter).second;
	}
	return nullptr;
}

bool ParserState::addNextState(string key, ParserState* s)
{
	return nextStates.insert({ key,s }).second;
}
bool ParserState::addProduction(ProductionStack& p)
{
	// 备注没有处理好 isProcess
	return productions.insert(p).second;    //如果插入成功返回true
}

bool ParserState::addProductionAsMerge(ProductionStack& p) {
	// 入股采用merge follow set的方式来插入产生式p，那么返回true，如果是全新添加的返回false
	for (set<ProductionStack>::iterator iter = productions.begin(); iter != productions.end(); iter++) {
		//ProductionStack& ip = const_cast<ProductionStack&>(*iter);  //由于set的迭代器对象默认是const类型，需要修改set元素的属性，需要进行强转
		ProductionStack ip = *iter;    //防止出错采用了比较保守的 先删除再插入，这样会进行排序方便后续的比较
		if (ip.isProductionEuqal(p)) {
			//如果两个产生式，的表达式是相同的
			if (ip.insertFollowSets(p.get_followSet())) {				//将参数的follow集 合并到原本的产生式中
				//如果增加了新的follow集合，把待处理项置为false
				ip.set_isProcess(false);
			}
			productions.erase(iter);   
			productions.insert(ip);
			return true;
		}
	}
	//如果没有就插入
	ProductionStack p1 = p;
	return productions.insert(p1).second;
}
set<string> ParserState::convertFirstSetToString(set<Node*>& firstset) {
	set<string> output = set<string>();
	for (auto iter = firstset.begin(); iter != firstset.end(); iter++) {
		output.insert((*iter)->get_node_name());
	}
	return output;
}
void ParserState::printState()const {
	cout << "state: " << stateID << endl;
	for (auto iter = productions.begin(); iter != productions.end(); iter++) {
		(*iter).printProduction();
		cout << endl;
	}
	for (auto iter = nextStates.begin(); iter != nextStates.end(); iter++) {
		cout << "input:" << (*iter).first << " --> state" << (*iter).second->get_stateID() << endl;
	}
 }
void ParserState::outputStateAsFile(ofstream& fout)const {
	fout << "state: " << stateID << endl;
	for (auto iter = productions.begin(); iter != productions.end(); iter++) {
		(*iter).outputProductionAsFile(fout);
		fout << endl;
	}
	for (auto iter = nextStates.begin(); iter != nextStates.end(); iter++) {
		fout << "input:" << (*iter).first << " --> state" << (*iter).second->get_stateID() << endl;
	}
}
const unordered_map<string, ParserState*>& ParserState::getNextStates()const {
	return nextStates;
}
ParserState::~ParserState()
{
}
