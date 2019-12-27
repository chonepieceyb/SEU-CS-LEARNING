#include "BottomUpParser.h"

BottomUpParser::BottomUpParser(set<string>ts, set<string> ns, vector<vector<string>> ps, string begin , string end , string none )
	:terminators(ts),nonTerminators(ns), string_productions(ps),begin(begin),end(end),none(none)
{
	//可以直接初始化一个 pm 了,生成所需要的所有节点
	pm = ProductionManager();
	int j_id = 0;
	for (auto iter = ts.begin(); iter != ts.end(); iter++) {
		Terminator t = Terminator(*iter);  //终结符
		pm.addTerminator(*iter,t);        //按值传递
		if (t.get_node_name() != none) {
			tableItems_map.insert({ t.get_node_name(),j_id });
			tableItems.push_back(t.get_node_name());
			j_id++;
		}
	}
	for (auto iter = ns.begin(); iter != ns.end(); iter++) {
		NonTerminator nt = NonTerminator(*iter);  //生成非终结符
		pm.addNonTerminator(*iter, nt);        //按值传递
		tableItems_map.insert({ nt.get_node_name(),j_id });
		tableItems.push_back(nt.get_node_name());
		j_id++;
	}
	for (auto iter = ps.begin(); iter != ps.end(); iter++) {
		string n = (*iter)[0];
		(*iter).erase((*iter).begin());      //移除第一个元素， 第一个是 产生式的头
		pm.addProduction(n, (*iter));
	}
	int base = 0;
	for (auto iter = ns.begin(); iter != ns.end(); iter++) {
		// 将每一个非终结符映射一个基地址（int ),为了将每一个产生式和一个int 对应，对所有的产生式进行编号。，方便规约
		production_base_id.insert({(*iter), base});
		base += pm.getProductionsNum(*iter);
		// 将每个非终结符映射为一个地址范围（int)
		for (int i = 0; i < pm.getProductionsNum(*iter); i++) {
			this->production_base_head.push_back(*iter);
		}
	}
	pm.calAllFirstSet(begin);
}

vector<pair<string, int>>  BottomUpParser::getOperations(int state, string input)const {
	vector<pair<string, int>> operations = vector<pair<string, int>>();
	if (state < 0 || state >= parserTable.size()) {
		//如果状态不对
		return operations;
	}
	auto i_iter = this->tableItems_map.find(input);
	if (i_iter == tableItems_map.end()) {
		// 如果输入的字符不在分析表里
		return operations;
	}
	int input_id = i_iter->second;
	return parserTable[state][input_id];
}

Production BottomUpParser::getProductionById(int p_id) {
	string head = this->production_base_head[p_id];
	int production_id = p_id - (*production_base_id.find(head)).second;
	return pm.generateProduction(head, production_id);
}
void BottomUpParser::printPaserTable(const int width, const int height)const {
	// 打印表头
	cout << setw(width)<<" "; 
	for (auto iter = tableItems.begin(); iter != tableItems.end(); iter++) {
		if (*iter == begin)    //扣除文法开始符号
			continue;
		cout << setiosflags(ios::right) << setw(width) << *iter;
	}
	for (int i = 0; i < height; i++) {
		cout << endl;
	}
	// 打印表格内容
	//vector<vector<std::pair<string,int>>>
	for (int i = 0; i < parserTable.size(); i++) {
		cout << setw(width) << i;   //状态名
		vector<vector<pair<string, int>>>  stateline = parserTable[i];
		int maxline = 1;
		// 找到需要输出的行数
		for (int j = 0; j < stateline.size(); j++) {
			if (this->tableItems[j] == begin)
				continue;
			if (stateline[j].size() > maxline) {
				maxline = stateline[j].size();
			}
		}
		for (int line = 0; line < maxline; line++) {
			//分行输出
			if (line > 0) {
				cout << setw(width) << "";
			}
			for (int j = 0; j < stateline.size(); j++) {
				if (this->tableItems[j] == begin)    //扣除文法开始符号
					continue;
				if (line >= stateline[j].size()) {
					cout << setw(width) << "";
				}
				else {
					cout << setw(width) << stateline[j][line].first + to_string(stateline[j][line].second);
				}			
			}
			cout << endl;
		}
		maxline = 0;
		// 换行
		for (int i = 0; i < height-1; i++) {
			cout << endl;
		}
	}
}

void  BottomUpParser::outPaserTableAsFile(ofstream& fout, const int width , const int height )const {
	// 打印表头
	fout << setw(width) << " ";
	for (auto iter = tableItems.begin(); iter != tableItems.end(); iter++) {
		if (*iter == begin)    //扣除文法开始符号
			continue;
		fout << setiosflags(ios::right) << setw(width) << *iter;
	}
	for (int i = 0; i < height; i++) {
		fout << endl;
	}
	// 打印表格内容
	//vector<vector<std::pair<string,int>>>
	for (int i = 0; i < parserTable.size(); i++) {
		fout << setw(width) << i;   //状态名
		vector<vector<pair<string, int>>>  stateline = parserTable[i];
		int maxline = 1;
		// 找到需要输出的行数
		for (int j = 0; j < stateline.size(); j++) {
			if (this->tableItems[j] == begin)
				continue;
			if (stateline[j].size() > maxline) {
				maxline = stateline[j].size();
			}
		}
		for (int line = 0; line < maxline; line++) {
			//分行输出
			if (line > 0) {
				fout << setw(width) << "";
			}
			for (int j = 0; j < stateline.size(); j++) {
				if (this->tableItems[j] == begin)    //扣除文法开始符号
					continue;
				if (line >= stateline[j].size()) {
					fout << setw(width) << "";
				}
				else {
					fout << setw(width) << stateline[j][line].first + to_string(stateline[j][line].second);
				}
			}
			fout << endl;
		}
		maxline = 0;
		// 换行
		for (int i = 0; i < height - 1; i++) {
			fout << endl;
		}
	}
}
void BottomUpParser::printStack(vector<int> state_stack, vector<string> string_stack, vector<token> input, int begin) {
	cout << "state stack: { ";
	if (state_stack.size ()> 0) {
		cout << state_stack[0];
	}
	for (int i = 1; i < state_stack.size(); i++) {
		cout <<","<< state_stack[i];
	}
	cout << " }";
	cout << endl;
	cout << "state stack: { ";
	if (string_stack.size()> 0) {
		cout << string_stack[0];
	}
	for (int i = 1; i < string_stack.size(); i++) {
		cout << "," << string_stack[i];
	}
	cout << " }";
	cout << endl;
	cout << "input token:";
	if (begin < input.size()) {
		cout << input[begin];
	}
	for (int i = begin + 1; i <input.size(); i++) {
		cout << "," << input[i];
	}
 }

void BottomUpParser::outputStackAsFile(ofstream& fout, vector<int> state_stack, vector<string> string_stack, vector<token> input, int begin) {
	fout << "state stack: { ";
	if (state_stack.size() > 0) {
		fout << state_stack[0];
	}
	for (int i = 1; i < state_stack.size(); i++) {
		fout << "," << state_stack[i];
	}
	fout << " }";
	fout << endl;
	fout << "string stack: { ";
	if (string_stack.size() > 0) {
		fout << string_stack[0];
	}
	for (int i = 1; i < string_stack.size(); i++) {
		fout << "," << string_stack[i];
	}
	fout << " }";
	fout << endl;
	fout << "input token: ";
	if (begin < input.size()) {
		fout << input[begin];
	}
	for (int i = begin + 1; i < input.size(); i++) {
		fout << "," << input[i];
	}
 }
 void BottomUpParser::outProductionsAsFile(ofstream& fout) {
	 int productionNum = 0;
	 for (auto iter = nonTerminators.begin(); iter != nonTerminators.end(); iter++) {
		 productionNum +=  pm.getProductionsNum(*iter);
	}
	 for (int i = 0; i < productionNum; i++) {
		 fout << "(" << i << ") ";
		 getProductionById(i).outputProductionAsFile(fout);
		 fout << endl;
	 }
}
 void  BottomUpParser::sloveAmbiguousTable(vector< pair<int, pair<string, int>>> deleteOperations) {
	 for (int i = 0; i < deleteOperations.size(); i++) {
		 pair<int, pair<string, int>> deleteOperation = deleteOperations[i];
		 int state_id = deleteOperation.first;
		 string input = deleteOperation.second.first;
		 int delete_id = deleteOperation.second.second;
		 auto input_iter = tableItems_map.find(input);
		 if (input_iter == tableItems_map.end()) {
			 continue;
		 }
		 int input_id = input_iter->second;
		 if (delete_id >= parserTable[state_id][input_id].size()) {
			 continue;
		 }
		 else {
			 parserTable[state_id][input_id].erase(parserTable[state_id][input_id].begin() + delete_id);
		 }
		}
}
bool BottomUpParser::scanTokenStream(vector<token> tokenstream, string analyze_report_dir) {
	/*
	tokenstream : token流
	analyze_report_dir : 语法分析报告路径， 生成堆栈推导顺序，语法树
	analysis_model_dir: 语法分析模型路径，生成分析语法所用的状态图和 分析表
	*/
	ofstream fout1 = ofstream();
	fout1.open(analyze_report_dir, ios::out);
	if (!fout1.is_open()) {
		cout << "无法打开报告结果文本" << endl;
		return false;
	}
	vector<int> state_stack = vector<int>();     //状态栈
	vector<string> string_stack = vector<string>(); //符号栈
	vector<treeNode> tree_stack = vector<treeNode>();  //语法树节点栈，用来生成语法树
	vector<int> tree_poses = vector<int>();  // 用来生成语法树
	SyntaxTree tree = SyntaxTree();   //语法树
	// 输入栈就是tokenstream;
	state_stack.push_back(0);   //初始状态为0
	string_stack.push_back(end);  //加入 终止符
	tokenstream.push_back(token(-1, end, "_"));    //在token流的末尾加入终结符， token的 ID是 -1 防止和正常token冲突
	int step = 0;
	fout1 << "---------------------step" << step << "---------------------------" << endl;
	outputStackAsFile(fout1, state_stack, string_stack, tokenstream, step);    //输出堆栈状态
	fout1 << endl;
	int input_pos = 0;
	for (auto t_iter = tokenstream.begin(); t_iter != tokenstream.end(); t_iter++) {
		int iter_shift = 0;                    //因为采用了 goto这种方法，需要控制迭代器不继续网下
		// 遍历输入的token流
		string input = t_iter->get_token_name();   //获得输入
checkAgain:	int state = state_stack.back();     // 取状态栈当前状态
		vector<pair<string, int>> operations = getOperations(state, input);
		if (operations.size() == 0) {
			//如果啥都没有，爆语法错误, 同时打印当前的堆栈状态
			cout << "Syntax error! can not generate Syntax tree";
			printStack(state_stack, string_stack, tokenstream, step);
			cout << endl;
			fout1 << "Syntax error! can not generate Syntax tree";
			outputStackAsFile(fout1,state_stack, string_stack, tokenstream, step);
			fout1 << "#############Syntax tree############" << endl;
			tree.outputTreeAsFile(fout1);
			fout1 << endl;
			fout1.close();
			return false;
		}
		else if (operations.size() > 1) {
			// 如果表中同时有两项 ， 证明分析器存在二义性
			cout << "Ambiguous parser table! check your parser table and your grammer!"<<endl;
			fout1 << "Ambiguous parser table! check your parser table and your grammer!" << endl;
			fout1 << "#############Syntax tree############" << endl;
			tree.outputTreeAsFile(fout1);
			fout1.close();
			return false;
		}
		else {
			pair<string, int > operation = operations[0];
			//如果成功找到操作，且只有一个
			if (operation.first == "S") {
				//如果是产生式
				state_stack.push_back(operation.second);       //移如新状态
				string_stack.push_back(input);                     //符号栈增加新的符号
				if (iter_shift == 0) {
					// 当前的input就是 输入栈内当前的节点
					treeNode t_n = treeNode(*t_iter);
					while (tree_poses.size() > 0) {
						t_n.child_ptrs.push_back(tree_poses.back());    // 设置父节点的孩子指针， 父节点是产生式的左边
						tree_poses.pop_back();
					}
					tree_stack.push_back(t_n);
				}
				else {
					token t = token(-1, input, "_");
					treeNode t_n = treeNode(t);
					while (tree_poses.size() > 0) {
						t_n.child_ptrs.push_back(tree_poses.back());    // 设置父节点的孩子指针， 父节点是产生式的左边
						tree_poses.pop_back();
					}
					tree_stack.push_back(t_n);
				}
				tree_poses.clear();                    //清空堆栈
				t_iter += iter_shift;
				input_pos+= iter_shift;
				iter_shift = 0;
				step++;
				input_pos++;
				fout1 << "---------------------step" << step << "---------------------------" << endl;
				outputStackAsFile(fout1, state_stack, string_stack, tokenstream, input_pos);    //输出堆栈状态
				fout1 << endl;
				
			}
			else if (operation.first == "R") {
				//如果是规约式
				Production p = getProductionById(operation.second);   // 根据 id 得到 相应的产生式
				step++;
				fout1 << "---------------------step" << step << "---------------------------" << endl;
				outputStackAsFile(fout1, state_stack, string_stack, tokenstream, input_pos);    //输出堆栈状态
				fout1 << "\nR" << operation.second << ": ";
				p.outputProductionAsFile(fout1);
				fout1 << endl;
				//将符号栈内的 产生式p右边的符号用 产生式的head代替，eg S -> ab ; 将 ab 用S代替
				//将产生式右边的符号消除
				for (int i = 0; i < p.getProductionSize();i++) {
					string_stack.pop_back();   
					state_stack.pop_back();                  //弹出状态;
					tree_poses.push_back(tree.addNode(tree_stack.back()));
					tree_stack.pop_back();
				}
				input = p.get_head()->get_node_name();   //当前的输入变成了 产生式 p的head了 
				if (input == begin ) {
					// 如果归约得到文法开始符号,归约成功，出口条件
					token t = token(-1, input, "_");          //把S1加入语法树
					treeNode t_n = treeNode(t);
					while (tree_poses.size() > 0) {
						t_n.child_ptrs.push_back(tree_poses.back());    // 设置父节点的孩子指针， 父节点是产生式的左边
						tree_poses.pop_back();
					}
					tree.addNode(t_n);
					fout1 << "sucess!" << endl;
					fout1 << "#############Syntax tree############" << endl;
					tree.outputTreeAsFile(fout1);
					fout1.close();
					return true;       
				}
				if (iter_shift == 0) {
					iter_shift--;        
				} 
				// 否则接着归约
			
				goto checkAgain;                    // 将p 产生式的 head作为输入字符重复进行判断， 无条件跳转
			}
			else {
				cout << "There are something wrong with parser table" << endl;
				fout1 << "There are something wrong with parser table" << endl;
				fout1 << "#############Syntax tree############" << endl;
				tree.outputTreeAsFile(fout1);
				fout1.close();
				return false;
			}
			
		}
		
	}
	if (state_stack.size() > 1 || string_stack.size() > 1) {
		//如果所有都读完了，栈内还有内容，返回false；
		cout << "Syntax error! can not generate Syntax tree";
		printStack(state_stack, string_stack, tokenstream, tokenstream.size() - 1);
		cout << endl;
		fout1 << "Syntax error! can not generate Syntax tree";
		outputStackAsFile(fout1, state_stack, string_stack, tokenstream, step);
		fout1 << endl;
		fout1.close();
		return false;
	}
}
BottomUpParser::~BottomUpParser()
{
}
