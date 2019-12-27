#include "Production.h"



Production::Production(NonTerminator* head, int production_id):head(head),production_id(production_id)
{
}

void Production::printProduction()const {
	cout << head->get_node_name() << " --> ";
	vector<Node*> production = head->getProduction(production_id);
	for (auto iter = production.begin(); iter != production.end(); iter++) {
		cout << (*iter)->get_node_name() << " ";
	}
}
void Production::outputProductionAsFile(ofstream& fout)const{
	fout << head->get_node_name() << " --> ";
	vector<Node*> production = head->getProduction(production_id);
	for (auto iter = production.begin(); iter != production.end(); iter++) {
		fout << (*iter)->get_node_name() << " ";
	}
}
set<string> Production :: getFirstSet() {
	return head->calFirstSet(this->production_id);
}
int  Production::getProductionSize()const {
	return head->getProductionSize(production_id);
}
Production::~Production()
{
}
