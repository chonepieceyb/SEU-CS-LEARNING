#include "NonTerminator.h"



NonTerminator::NonTerminator(string node_name) :Node(node_name)
{

}
NonTerminator::NonTerminator(int node_id, string node_name, string node_value) : Node(node_id, node_name, node_value)
{

}
NonTerminator::~NonTerminator() {

}

void NonTerminator::addDerivativeNode( int production_id,Node& n) {
	productions[production_id].push_back(&n);
}

void NonTerminator::addProduction(vector<Node*> p) {
	productions.push_back(p);
}

int NonTerminator::getProductionNum()const {
	return productions.size();  //可能犯错
}
int NonTerminator::getProductionSize(int production_id)const {
	if (production_id >= int(productions.size())) {
		return -1;         //-1是错误码
	}
	return productions[production_id].size();
}
Node*  NonTerminator::getNodeInProduction(int production_id, int stack_id) {
	if (production_id >= int( productions.size())) {
		return nullptr;
	}
	if (stack_id >= int(productions[production_id].size())) {
		return nullptr;
	}
	return productions[production_id][stack_id];
}

vector<Node*>   NonTerminator::getProduction(int production_id)const {
	return productions[production_id];
}

set<string> NonTerminator::calFirstSet( int production_id, int stack_id) {
	vector<Node*> p = productions[production_id];
	set<string> fset = set<string>();
	for (auto n_iter = p.begin()+ stack_id; n_iter != p.end(); n_iter++) {
		//内层循环遍历产生式的节点
		set<string> subfirstSet = (*n_iter)->get_firstSet();
			fset.insert(subfirstSet.begin(), subfirstSet.end());   //获得当前节点的first集，  这里注意 节点的全局的first集都已经算完了
		if (fset.erase("none") > 0) {    //如果包含产生 空串的非终结符，注意remove函数已经把空串移除了
			if (n_iter + 1 == p.end()) {
				//如果已经遍历到最后一个节点，而且存在空串边（前面每一个都存在空串边）,加入空串边
				fset.insert("none");
			}
			continue;            //因为存在空串边，还要继续往下遍历
		}
		else {
			break;               //否则就不继续往下做了，跳出第一层循环
		}

	}
	return fset;
}

set<string> NonTerminator::calFirstSet(set<string> called_stack) {
	// call_stack存放着调用顺序的一个集合，用来防止出现回路，导致无限递归
	while (true) {
		bool need_loop = false;
		int original_size = this->firstSet.size();
		for (auto p_iter = productions.begin(); p_iter != productions.end(); p_iter++) {
			//外层循环遍历产生式
			for (auto n_iter = (*p_iter).begin(); n_iter != (*p_iter).end(); n_iter++) {
				//内层循环遍历产生式的节点
				// 看下一个节点有没有出现在 调用栈内
				if (called_stack.find((*n_iter)->get_node_name()) == called_stack.end()) {
					//不存在回路才递归调用 计算 first集合,并将当前节点的first集插入, 如果存在回路就先跳过
					set<string> newCalled_stack = called_stack;
					newCalled_stack.insert(node_name);
					set<string> subfirstSet = set<string>();
					if ((*n_iter)->get_calAgain() == false) {
						subfirstSet = (*n_iter)->get_firstSet();
					}
					else {
						subfirstSet = (*n_iter)->calFirstSet(newCalled_stack);//递归遍历所有的node，如果是非终结符会返回只包含指向自己的指针的vector，递归调用
					}
					this->firstSet.insert(subfirstSet.begin(), subfirstSet.end());
				}
				else {
					//如果存在回路需要再做一次
					need_loop = true;
				}
				if (this->firstSet.erase("none")>0) {    //如果包含产生 空串的非终结符，注意erase函数已经把空串移除了
					if (n_iter + 1 == (*p_iter).end()) {
						//如果已经遍历到最后一个节点，而且存在空串边（前面每一个都存在空串边）,加入空串边
						this->firstSet.insert("none");
					}
					continue;            //因为存在空串边，还要继续往下遍历
				}
				else {
					break;               //否则就不继续往下做了，跳出第一层循环
				}

			}
			
		}
		// 算完了 , 而且没有在递归调用序列里，之后不用再算了
		if (called_stack.find(node_name) == called_stack.end()) {
			this->calAgain = false;
		}
		if (this->firstSet.size() == original_size || need_loop == false) {
			break;    //只有不再扩充了才跳出去
		}
	}
	return this->firstSet;
	
}
