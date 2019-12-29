#include "LR1State.h"
#include<cassert>


LR1State::LR1State(int state_ID):ParserState(state_ID)
{
}


LR1State::~LR1State()
{
}
void LR1State::calFollowSet(ProductionStack& p, set<ProductionStack>& fps)
{
	string name = p.get_head()->get_node_name();
	//计算follow集, p会根据state当前productions 里 所有的production来计算自己的follow set,一定要注意是当前state下的production
	for (auto p_iter = fps.begin(); p_iter != fps.end(); p_iter++) {
		//遍历当前fps中所有的产生式
		//ProductionStack& op = const_cast<ProductionStack&>(*p_iter);  //对set迭代器对象强行改变const属性
		ProductionStack  op = *p_iter;
		Node* currentNode = op.get_head()->getNodeInProduction(op.get_production_id(), op.get_stackState());
		
		if (currentNode!=nullptr && currentNode->get_node_name() == p.get_head()->get_node_name()) {
			//如果产生式中的非终结符相同，计算follow集合
			//先计算产生式之后符号的first集合
			set<string>firstSetS = op.get_head()->calFirstSet(op.get_production_id(), op.get_stackState() + 1);
			auto none_iter = firstSetS.find("none");
			if (none_iter != firstSetS.end()|| firstSetS.size()==0) {
				//在first集合中存在空串边，合并first和原本表达式的follow
				//先把 none去除掉
				if(firstSetS.size() != 0)
					firstSetS.erase(none_iter);
				//设置follow集合为first集
				p.set_followSet(firstSetS);
				//合并first集和follow
				p.insertFollowSets(op.get_followSet());
			}
			else {
				//否则只为 first集， 这里first集没有none
				p.set_followSet(firstSetS);
			}
		}
	}
	
}
void LR1State::stateGrow(ProductionManager& pm)
{
	int id = stateID;
	// 状态生长函数，从state里的一个state扩展到直到无法继续扩展
	while (true) {
		//每次扩展完就从头遍历
		bool processAgain = false;
		for (auto fp_iter = productions.begin(); fp_iter != productions.end(); fp_iter++) {
			//从头开始看能否产生新的产生式
			// 现在的set里的都是已经算完的
			ProductionStack& fp = const_cast<ProductionStack&>(*fp_iter);  //强转
			if (fp.get_isProcess() == false) {
				//如果有还没有处理的产生式，就设置processAgain为true，知道所有的产生式都被处理了，跳出while循环
				processAgain = true;
			}
			else {
				continue;  //跳过已经处理完成的式子
			}
			fp.set_isProcess(true);  //标记已经看过这个产生式了
			Node* currentNode = fp.get_head()->getNodeInProduction(fp.get_production_id(), fp.get_stackState());
			if (currentNode == nullptr) {
				continue;    //如果没找到证明小点已经到最后了。
			}
			if (dynamic_cast<NonTerminator*>(currentNode) != nullptr) {
				//如果是非终结符，需要产生新的产生式
				vector<ProductionStack> newProductions = pm.generateProductionStacks(currentNode->get_node_name());
				set<ProductionStack> fps = set<ProductionStack>();
				fps.insert(fp);
				for (auto np_iter = newProductions.begin(); np_iter != newProductions.end(); np_iter++) {
					calFollowSet((*np_iter), fps);        //计算follow集合,注意这里计算完会直接对np_iter的内容进行修改
					if (addProductionAsMerge((*np_iter))) {
						//加入新产生式，
						fp_iter = productions.begin();  //防止出bug
					}
				}
			}
		}
		if (!processAgain) {
			break;
		}
	}
}
bool LR1State::operator==(const ParserState& p)const
{	
	return productions == p.get_productions();   //两个状态是否相等的标准是它们的产生式是否相同,可能出错
}
bool LR1State::operator<(const ParserState& p)const
{
	bool issmall;
	if (this->productions < p.get_productions()) {
		issmall = true;
	}
	else {
		issmall = false;
	}
	return issmall;
}
