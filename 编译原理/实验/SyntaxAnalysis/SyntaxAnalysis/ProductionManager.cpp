#include "ProductionManager.h"



ProductionManager::ProductionManager()
{
}


ProductionManager::~ProductionManager()
{
}
bool ProductionManager::addNonTerminator(string name, NonTerminator& n)
{
	auto iter = nonTerminators.find(name);
	if (iter == nonTerminators.end()) {
		//如果没有
		nonTerminators.insert({ name,n });
		return true;
	}
	else {
		return false;
	}
}
bool ProductionManager::addTerminator(string name, Terminator& t) {
	auto iter = terminators.find(name);
	if (iter == terminators.end()) {
		//如果没有
		terminators.insert({ name,t });
		return true;
	}
	else {
		return false;
	}
}
bool ProductionManager::addProduction(string nonterminator, vector<string> production) {
	auto non_iter = nonTerminators.find(nonterminator);
	if (non_iter == nonTerminators.end())
	{
		//没找到
		return false;
	}
	vector<Node*> p = vector < Node* >();
	for (auto string_iter = production.begin(); string_iter != production.end(); string_iter++) {
		//遍历产生式
		auto iter1 = nonTerminators.find(*string_iter);
		auto iter2 = terminators.find(*string_iter);
		if (!(iter1 == nonTerminators.end() && iter2 == terminators.end()) &&
			!(iter1 != nonTerminators.end() && iter2 != terminators.end())) {
			//异或运算，不可能都有不可能都没有
			if (iter1 != nonTerminators.end()) {
				Node& n = (*iter1).second;   //子类转父类
				p.push_back(&n);
				continue;
			}
			if (iter2 != terminators.end()) {
				Node& n = (*iter2).second;   //子类转父类
				p.push_back(&n);
			}
		}
		else {
			return false;
		}
	}
	(*non_iter).second.addProduction(p);
	return true;
}

ProductionStack ProductionManager::generateProductionStack(string n_key, int production_id) {
	//特别注意内存问题,production存放的都不涉及内存，所以简单的浅拷贝就可以
	// production_id 是 下标索引从 0 开始
	auto iter = nonTerminators.find(n_key);
	if (iter == nonTerminators.end()) {
		//如果没找到
		return ProductionStack(nullptr, -1);
	}
	if (production_id >= (*iter).second.getProductionNum()) {
		//没有这个产生式
		return ProductionStack(nullptr, -1);
	}
	return ProductionStack(&((*iter).second), production_id);
}
vector<ProductionStack> ProductionManager::generateProductionStacks(string n_key) {
	vector<ProductionStack> productions = vector<ProductionStack>();
	auto iter = nonTerminators.find(n_key);
	if (iter == nonTerminators.end()) {
		//如果没找到
		return productions;
	}
	for (int i = 0; i < (*iter).second.getProductionNum(); i++) {
		productions.push_back(ProductionStack(&((*iter).second), i));
	}
	return productions;
}

Production ProductionManager::generateProduction(string n_key, int production_id) {
	auto iter = nonTerminators.find(n_key);
	if (iter == nonTerminators.end()) {
		//如果没找到
		return Production(nullptr, -1);
	}
	if (production_id >= (*iter).second.getProductionNum()) {
		//没有这个产生式
		return Production(nullptr, -1);
	}
	return Production(&((*iter).second), production_id);
}

vector<Production> ProductionManager::generateProductions(string n_key) {
	vector<Production> productions = vector<Production>();
	auto iter = nonTerminators.find(n_key);
	if (iter == nonTerminators.end()) {
		//如果没找到
		return productions;
	}
	for (int i = 0; i < (*iter).second.getProductionNum(); i++) {
		productions.push_back(Production(&((*iter).second), i));
	}
	return productions;
}
int  ProductionManager::getProductionsNum(string n_key) {
	auto iter = nonTerminators.find(n_key);
	if (iter == nonTerminators.end()) {
		//如果没找到
		return 0;
	}
	else {
		return (*iter).second.getProductionNum();
	}
}
vector<ProductionStack> ProductionManager::derivateProductions(ProductionStack p) {
	vector<ProductionStack> outputs = vector<ProductionStack>();
	NonTerminator* nt_ptr = p.get_head();  //首指针
	Node* n = nt_ptr->getNodeInProduction(p.get_production_id(), p.get_stackState());
	if (n == nullptr) {
		return outputs;         //如果 没找到， 按照理论，如果没找到应该 100% 的概率因为stack_id已经到最后了
	}
	n = dynamic_cast<NonTerminator*>(n);    //这里由于 在Node类中我使用了虚析构函数，所以这句话应该能够判断。
	if (n == nullptr) {
		//不是非终结符就不用产生式子了,注意在外面还要再判断一次，上下两个语句都返回假的条件
		return outputs;
	}
	//是非终结符，产生新的产生式
	outputs = generateProductionStacks(n->get_node_name());
	return outputs;
}
void ProductionManager::calAllFirstSet(string begin) {
	for (auto iter = terminators.begin(); iter != terminators.end(); iter++) {
		set<string> stack;
		iter->second.calFirstSet(stack);
	}
	for (auto iter = nonTerminators.begin(); iter != nonTerminators.end(); iter++) {
		set<string> stack;
		iter->second.calFirstSet(stack);
	}
}