#include "ProductionStack.h"



ProductionStack::ProductionStack(NonTerminator* head, int production_id):Production( head,  production_id)
{
	stateInit();
}


bool ProductionStack::operator==(const ProductionStack& p)const {
	if (this->get_head() == p.get_head() &&
		this->get_production_id() == p.get_production_id() &&
		this->followSet == p.followSet&&
		this->get_stackState() == p.get_stackState()
		) {
		return true;
	}
	else {
		return false;
	}
}
bool ProductionStack::operator<(const ProductionStack& p)const {
	//排序优先级
	bool issmall;
	if (this->get_head()->get_node_name() < p.get_head()->get_node_name()) {
		issmall =  true;
	}
	else if (this->get_head()->get_node_name() == p.get_head()->get_node_name()) {
		if (this->get_production_id() < p.get_production_id()) {
			issmall = true;
		}
		else if (this->get_production_id() == p.get_production_id()) {
			if (this->followSet < p.get_followSet()) {
				issmall = true;
			}
			else if (this->followSet == p.get_followSet()) {
				if (this->get_stackState() < p.get_stackState()) {
					issmall = true;
				}else{
					issmall = false;
				}
			}
			else {
				issmall = false;
			}
		}
		else {
			issmall = false;
		}
	}
	else {
		issmall = false;
	}
	
	return issmall;
	/*
	if (this->followSet < p.followSet) {
		return true;
	}
	if (this->get_stackState() <= p.get_stackState()) {
		return true;
	}
	*/
}
bool ProductionStack::operator>(const ProductionStack& p) const{
	return !((*this) < p || (*this) == p);   // ！（*this <= p)
}

 bool ProductionStack::isProductionEuqal(ProductionStack& p) {
	 if (this->get_head()->get_node_name() == p.get_head()->get_node_name() &&
		 this->get_production_id() == p.get_production_id()&& 
		 this->get_stackState() == p.get_stackState())
		 return true;
	 return false;

}

void ProductionStack::printProduction()const {
	cout << head->get_node_name() << " --> ";
	vector<Node*> production = head->getProduction(production_id);
	for (int i = 0; i < int(production.size());i++) {
		if (i == stackState) {
			cout<<"." << production[i]->get_node_name() << " ";
		}
		else {
			cout  << production[i]->get_node_name() << " ";
		}	
	}
	if (stackState == production.size()) {
		cout << ".";
	}
	auto iter = followSet.begin();
	if (iter != followSet.end()) {
		cout << "{ " << *followSet.begin();
		iter++;
	}
	else {
		cout << "{ ";
	}
	
	for (iter; iter != followSet.end(); iter++) {
		cout << "," << *iter;
	}
	cout << "}";
 }
void  ProductionStack::outputProductionAsFile(ofstream& fout) const{
	fout << head->get_node_name() << " --> ";
	vector<Node*> production = head->getProduction(production_id);
	for (int i = 0; i < int(production.size()); i++) {
		if (i == stackState) {
			fout << "." << production[i]->get_node_name() << " ";
		}
		else {
			fout << production[i]->get_node_name() << " ";
		}
	}
	if (stackState == production.size()) {
		fout << ".";
	}
	auto iter = followSet.begin();
	if (iter != followSet.end()) {
		fout << "{ " << *followSet.begin();
		iter++;
	}
	else {
		fout << "{ ";
	}

	for (iter; iter != followSet.end(); iter++) {
		fout << "," << *iter;
	}
	fout << "}";
}
bool ProductionStack::insertFollowSets(set<string> set) {
	bool ischange = false;
	for (auto iter = set.begin(); iter != set.end(); iter++) {
		if (followSet.insert(*iter).second) {
			//如果插入了一个新值
			ischange = true;
		}
	}
	return ischange;
 }
 bool ProductionStack::insertFollowSet(string str) {
	 return followSet.insert(str).second;
 }
void ProductionStack::stateInit() {
	followSet = set<string>();
	stackState = 0;    //默认为0 也就是点在最左边
	isProcess = false;   //默认未处理
}
ProductionStack::~ProductionStack()
{
}
