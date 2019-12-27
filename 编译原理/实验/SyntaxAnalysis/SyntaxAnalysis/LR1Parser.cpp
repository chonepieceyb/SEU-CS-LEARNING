#include "LR1Parser.h"



LR1Parser::LR1Parser(set<string>ts, set<string> ns, vector<vector<string>> ps, string begin , string end, string none )
	:BottomUpParser(ts,ns,ps,begin,end,none)
{
}


LR1Parser::~LR1Parser()
{
}

void LR1Parser:: initStates(vector<std::pair<string, int>> productions, vector<set<string>> followset) {
	states.clear();
	LR1State state0 = LR1State(0);
	for (int i = 0; i<int(productions.size()); i++) {
		ProductionStack p = pm.generateProductionStack(productions[i].first, productions[i].second);
		p.set_followSet(followset[i]);
		state0.addProductionAsMerge(p);
	}
	states.insert(state0);
}
unordered_map<string, LR1State> LR1Parser::calNextStates( LR1State& s)
{
	unordered_map<string, LR1State> outputs = unordered_map<string, LR1State>();
	//计算该状态所有可能产生的状态
	set<ProductionStack> productions = s.get_productions();   //获取产生式
	for (auto p_iter = productions.begin(); p_iter != productions.end(); p_iter++) {
		//遍历所有产生式
		ProductionStack p = *p_iter;     
		int stack_id = p.get_stackState();
		Node* currentNode = p.get_head()->getNodeInProduction(p.get_production_id(), stack_id);
		if (currentNode == nullptr) {
			continue;       //如果小点在最右边了...
		}
		if (currentNode->get_node_name() == end || currentNode->get_node_name() == none) {
			continue;
		}
		string edge = currentNode->get_node_name();
		auto state_iter = outputs.find(edge);  //查找看有没有已经有这个状态了
		if (state_iter == outputs.end()) {
			//如果没有，新增一个state
			LR1State outputState = LR1State(-2);    //-2表示状态未初始化
			p.set_stackState(stack_id + 1);        //更新堆栈状态
			p.set_isProcess(false);               //重置处理状态
			outputState.addProductionAsMerge(p);  //增加表达式
			outputs.insert({ edge,outputState });
		}
		else {
			//如果已经有这个状态，就把产生式加进去
			p.set_stackState(stack_id + 1);        //更新堆栈状态
			p.set_isProcess(false);               //重置处理状态
			(*state_iter).second.addProductionAsMerge(p);  //加入表达式
		}

	}
	for (auto iter = outputs.begin(); iter != outputs.end(); iter++) {
		(*iter).second.stateGrow(pm);    //进行表达式的推导
	}
	return outputs;
}
void LR1Parser::buildParserGraph() {
	//构造状态图
	if (states.size() != 1) {
		//从初始状态开始构造，必须从1 开始
		cout << "初始状态数错误!!" << endl;
		return;
	}
	//先获得完整的初始状态,现在set只有一个初始状态,直接强转对引用操作
	LR1State& state0 = const_cast<LR1State&>(*states.begin());
	state0.stateGrow(pm);   
	int stateID = 1;                //从1开始添加state 因为state0 已经有了
	while (true) {
		bool isAgain = false;
		for (auto s_iter = states.begin(); s_iter != states.end(); s_iter++) {
			LR1State& currentS = const_cast<LR1State&>(*s_iter);   //使用强转，后面只改变process和nextedge，所以不需要先删除再加入，isProcess不影响集合排序，注意
			if ((*s_iter).get_isProcess() == false) {
				//如果是待处理项
				isAgain = true;
			}
			else {
				continue;    //否则跳过
			}
			// 设置该状态已查看
			currentS.set_isProcess(true);
			// 计算该状态可能的产生的状态
			unordered_map<string, LR1State> generatedStates =
				calNextStates(currentS);
			for (auto iter = generatedStates.begin(); iter != generatedStates.end(); iter++) {
				if (states.find((*iter).second) == states.end() ) {
					//如果新产生的状态，原来的状态里没有，加入新状态
					(*iter).second.set_stateID(stateID);   //设置状态编号
					stateID++;
					states.insert((*iter).second);         //加入状态
					auto next_iter = states.find((*iter).second);  //先插入，再增加
					ParserState& next_state = const_cast<LR1State& >(*next_iter);  //将子类指针强转为基类指针
					currentS.addNextState((*iter).first, &next_state);

				}
				else {
					//如果原来状态有 加边
					auto next_iter = states.find((*iter).second);
					ParserState& next_state = const_cast<LR1State&>(*next_iter);  //将子类指针强转为基类指针
					currentS.addNextState((*iter).first, &next_state);
				}
			}
		}
		if (isAgain == false) {
			break;
		}
	}
 }
void LR1Parser::printStates()const {
	for (auto iter = states.begin(); iter != states.end(); iter++) {
		(*iter).printState();
		cout << endl;
	}
}
void LR1Parser::outParserModel(ofstream& fout) {
	fout << "###############产生式#################" << endl;
	outProductionsAsFile(fout);
	fout << endl;
	fout << "###############状态图#################" << endl;
	outputStatesAsfile(fout);
	fout << endl;
	fout << "###############分析表#################" << endl;
	outPaserTableAsFile(fout,8,1);
}
void LR1Parser::outputStatesAsfile(ofstream& fout)const {
	for (auto iter = states.begin(); iter != states.end(); iter++) {
		(*iter).outputStateAsFile(fout);
		fout << endl;
	}
 }
void LR1Parser::buildParserTable() {
	//根据所有的 states构造LR1分析表
	parserTable = vector<vector<vector<std::pair<string, int>>>>(states.size());
	for (auto s_iter = states.begin(); s_iter != states.end(); s_iter++) {
		//遍历所有的状态
		vector<vector<pair<string, int>>> stateline = vector<vector<pair<string, int>>>(tableItems_map.size());  //新建一行，一个状态有一行
		set<ProductionStack> productions = (*s_iter).get_productions();
		//遍历所有产生式，看有没有归约项
		for (auto p_iter = productions.begin(); p_iter != productions.end(); p_iter++) {
			if ((*p_iter).get_stackState() == (*p_iter).getProductionSize())
			{
				//如果小点在最右边了，增加follow集下所有的规约式;
				set<string> followset = (*p_iter).get_followSet();
				for (auto p_iter1 = followset.begin(); p_iter1 != followset.end(); p_iter1++) {
					auto j_iter = tableItems_map.find(*p_iter1);
					if (j_iter != tableItems_map.end()) {    //这个跳过none
						int production_id = (*production_base_id.find(p_iter->get_head()->get_node_name())).second
							+ p_iter->get_production_id();
						stateline[(*j_iter).second] .push_back( make_pair("R", production_id));   //R是规约式
					}
				}
			}
		}
		//遍历所有状态机的边，看有没有产生项
		const unordered_map<string, ParserState*>& nextStates = s_iter->getNextStates();
		for (auto ns_iter = nextStates.begin(); ns_iter != nextStates.end(); ns_iter++) {
			// 遍历所有的下一个状态
			auto j_iter = tableItems_map.find(ns_iter->first);   //下一个读入的字符对应的列数
			stateline[j_iter->second] .push_back( make_pair("S", ns_iter->second->get_stateID()));  //S是产生式
		}
		// 完成在一个状态下的表的构建
		parserTable[s_iter->get_stateID()] = stateline;
	}
}


