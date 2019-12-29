#include"Node.h"
#include"LR1Parser.h"
#include"DFA.h"

//################################词法分析器所需要的额外函数 #################################
string s5edgeJudge(string s) {
	if (s != "\"" || s == "digit" || s == "letter") {
		return "chars1";
	}
	else {
		return s;
	}
}
string s7edgeJudge(string s) {
	if (s != "'" || s == "digit" || s == "letter") {
		return "chars2";
	}
	else {
		return s;
	}
}
string convertInput(char c) {
	if (isdigit(c)) {
		return string("digit");
	}
	else if (isalnum(c)) {
		return string("letter");
	}
	else {
		return string(1, c);
	}
}
int main() {
	const string inputfile = "D:\\input.txt";
	const string reportfile = "D:\\report.txt";
	const string modelfile = "D:\\model.txt";
	const string tokenfile = "D:\\token.txt";
	vector<token> tokenstream = vector<token>();
	//####################################### 词法分析模块 #######################################################//
	//构造状态机
	int stateNum = 10; // 有10个状态
	string edges[] = { "_", "letter","digit",".", "\"","chars1","'","chars2" }; //chars1代表除了”之外的字符，chars2 代表除了‘之外的字符
	//申请一个2维数组,初始化为-1
	vector<int>** stateM = new vector<int>*[stateNum];
	for (int i = 0; i < stateNum; i++) {
		stateM[i] = new vector<int>[stateNum];
		for (int j = 0; j < stateNum; j++) {
			stateM[i][j] = vector<int>();
		}
	}
	stateM[0][1] = vector<int>({ 0,1 });
	stateM[1][1] = vector<int>({ 0,1,2 });
	stateM[0][2] = vector<int>({ 2 });
	stateM[2][2] = vector<int>({ 2 });
	stateM[2][3] = vector<int>({ 3 });
	stateM[3][4] = vector<int>({ 2 });
	stateM[4][4] = vector<int>({ 2 });
	stateM[0][5] = vector<int>({ 4 });
	stateM[5][5] = vector<int>({ 5 });
	stateM[5][6] = vector<int>({ 4 });
	stateM[0][7] = vector<int>({ 6 });
	stateM[7][8] = vector<int>({ 7 });
	stateM[8][9] = vector<int>({ 6 });
	DFA myDFA = DFA();                     //终止符是空格
	myDFA.initStates(stateNum, stateM, edges);
	// 增加终止状态
	myDFA.addTokenItem(1, 0, "id"); // 1状态是终态 ， id(变量）
	myDFA.addTokenItem(2, 1, "num"); //2 状态终态 ， 数字
	myDFA.addTokenItem(4, 2, "num"); //4 状态终态 ， 数字
	myDFA.addTokenItem(6, 3, "string"); //6 状态 ，字符串
	myDFA.addTokenItem(9, 4, "char"); //9 状态 ，字符
	//增加保留字
	vector<string> keepWords= vector<string>({ "if","else","while","do","(",")","+","-","*","/", ";" ,"=","and","or","not",">","<",">=","<","==","!=" ,"true","false"
											 "id","num","then","{" ,"}" });
	for (int i = 0; i < keepWords.size(); i++) {
		myDFA.addKeepWord(keepWords[i], 5 + i);
	}
	// 附加边判断函数
	myDFA.getState(7).setEdgeJudgeFunction(s7edgeJudge);
	myDFA.getState(5).setEdgeJudgeFunction(s5edgeJudge);
	
	//######################### 扫描文件模块
	ifstream fin = ifstream();
	fin.open("D:\\input.txt", ios::in);
	if (!fin.is_open()) {
		cout << "无法打开文件流" << endl;
		return 0;
	}
	ofstream fout = ofstream();
	fout.open(tokenfile, ios::out);
	if (!fout.is_open()) {
		cout << "无法打开文件流" << endl;
		return 0;
	}
	string str;
	char c;
	bool isIgnore = false;
	while (fin.get(c)) {
		if ((c == ' ' || c == '\n' || c == '\t') && isIgnore == false) {
			if (str == "") {
				continue;
			}
			token t = myDFA.scan(str, convertInput);
			tokenstream.push_back(t);
			fout << t << endl;
			str.clear();
			continue;
		}
		else {
			if (c == '\"') {
				if (isIgnore == false) {
					isIgnore = true;
				}
				else {
					isIgnore = false;
				}
			}
			str += c;
		}
	};
	if (str != "") {
		token t = myDFA.scan(str, convertInput);
		tokenstream.push_back(t);
		fout << t << endl;
	}
	fin.close();
	//delete数组
	for (int i = 0; i < stateNum; i++) {
		if (stateM[i] != nullptr) {
			delete[] stateM[i];
		}
	}
	delete[] stateM;

	//########################################语法分析模块####################################################
	// 构造表达式，表达式定义的文法同 词法分析器 , 从表达式生成状态表

	set<string> nonTerminators = set<string>({ "S1","S","E","EA","EO","rop","C","T","WD","I" });
	set<string> terminators = set<string>({ "if","else","while","do","(",")","+","-","*","/", ";" ,"=","and","or","not",">","<",">=","<=","<","==","!=" ,"true","false",
											 "id","num","then","$","none","{","}" });
	vector < vector<string>> productions = vector < vector<string>>();
	productions.push_back(vector<string>({ "S1","S" }));
	productions.push_back(vector<string>({ "S","id","=","E" ,";"}));
	productions.push_back(vector<string>({ "S","S","S" }));
	productions.push_back(vector<string>({ "S","T","{","S","}" }));
	productions.push_back(vector<string>({ "S","C","{","S","}" }));
	productions.push_back(vector<string>({ "T","C","{","S","}","else" }));
	productions.push_back(vector<string>({ "C","if","(","E",")","then" }));
	productions.push_back(vector<string>({ "S","WD","{","S","}" }));
	productions.push_back(vector<string>({ "WD","while","(","E",")" ,"do"}));
	productions.push_back(vector<string>({ "E","EA","E" }));
	productions.push_back(vector<string>({ "E","EO","E" }));
	productions.push_back(vector<string>({ "E","not","E" }));
	productions.push_back(vector<string>({ "E","(","E",")" }));
	productions.push_back(vector<string>({ "E","E","rop","E" }));
	productions.push_back(vector<string>({ "EA","E","and" }));
	productions.push_back(vector<string>({ "EO","E","or" }));
	productions.push_back(vector<string>({ "E","id" }));
	productions.push_back(vector<string>({ "E","true" }));
	productions.push_back(vector<string>({ "E","false" }));
	productions.push_back(vector<string>({ "E","num" }));
	productions.push_back(vector<string>({ "rop",">" }));
	productions.push_back(vector<string>({ "rop",">=" }));
	productions.push_back(vector<string>({ "rop","<" }));
	productions.push_back(vector<string>({ "rop","<=" }));
	productions.push_back(vector<string>({ "rop","==" }));
	productions.push_back(vector<string>({ "rop","!=" }));
	productions.push_back(vector<string>({ "E","E" ,"+","E"}));
	productions.push_back(vector<string>({ "E","E" ,"-","E" }));
	productions.push_back(vector<string>({ "E","E" ,"*","E" }));
	productions.push_back(vector<string>({ "E","E" ,"/","E" }));

	LR1Parser myParser = LR1Parser(terminators, nonTerminators, productions);

	/*
	//#########################small demo ##################################
	set<string> terminators = set<string>({"none","$","a","b","c","d"});
	set<string> nonTerminators = set<string>({ "S1","S","A","B"});
	vector < vector<string>> productions = vector < vector<string>>();
	productions.push_back(vector<string>({ "S1","S" }));
	productions.push_back(vector<string>({ "S","A","a" }));
	productions.push_back(vector<string>({ "S","b","A","c" }));
	productions.push_back(vector<string>({ "S","B","c" }));
	productions.push_back(vector<string>({ "S","b","B","a" }));
	productions.push_back(vector<string>({ "S","S","S" }));
	productions.push_back(vector<string>({ "S","none" }));
	productions.push_back(vector<string>({ "A","d" }));
	productions.push_back(vector<string>({ "B","d" }));
	LR1Parser myParser = LR1Parser(terminators, nonTerminators, productions);
	*/
	//设置初始状态
	std::pair<string, int> p1 = make_pair("S1", 0);
	vector<std::pair<string, int>> ps = vector<std::pair<string, int>>();
	ps.push_back(p1);
	vector<set<string>> followset = vector<set<string>>({ set<string>{"$"} });
	myParser.initStates(ps, followset);
	myParser.buildParserGraph();
	myParser.buildParserTable();
	// 解决二义性问题
	

	vector < pair<int, pair<string, int>> >deleteOperations = vector < pair<int, pair<string, int>>>();
	deleteOperations.push_back(make_pair(48, make_pair("id", 1)));  // 83状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(47, make_pair("id", 1)));  // 84状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(79, make_pair("id", 1)));  // 84状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(48, make_pair("if", 1)));  // 83状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(47, make_pair("if", 1)));  // 84状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(79, make_pair("if", 1)));  // 84状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(48, make_pair("while", 1)));  // 83状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(47, make_pair("while", 1)));  // 84状态下读入分号 ，删除产生式
	deleteOperations.push_back(make_pair(79, make_pair("while", 1)));  // 83状态下读入分号 ，删除产生式
	//解决优先级和结合性带来的从图
	deleteOperations.push_back(make_pair(33, make_pair("!=", 0)));   //33 状态 S - > EA E  ，优先级比and高保留产生式， 优先级 <= and 保留规约式
	deleteOperations.push_back(make_pair(33, make_pair("+", 0)));    //左结合保留归约式
	deleteOperations.push_back(make_pair(33, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("<", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("<=", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("==", 0)));
	deleteOperations.push_back(make_pair(33, make_pair(">", 0)));
	deleteOperations.push_back(make_pair(33, make_pair(">=", 0)));
	deleteOperations.push_back(make_pair(33, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(33, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(34, make_pair("!=", 0)));   //34 状态 S - > E0 E  ，优先级比or高保留产生式(0)， 优先级 <= or 保留规约式(1)
	deleteOperations.push_back(make_pair(34, make_pair("+", 0)));    //左结合保留归约式
	deleteOperations.push_back(make_pair(34, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("<", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("<=", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("==", 0)));
	deleteOperations.push_back(make_pair(34, make_pair(">", 0)));
	deleteOperations.push_back(make_pair(34, make_pair(">=", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("and", 0)));
	deleteOperations.push_back(make_pair(34, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("!=", 1)));   //35 状态 S - > not E  ，优先级比not高保留产生式(0)， 优先级 <= not 保留规约式(1)
	deleteOperations.push_back(make_pair(35, make_pair("+", 1)));    //左结合保留归约式  
	deleteOperations.push_back(make_pair(35, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(35, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(35, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(35, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(37, make_pair("!=", 1)));   //37 状态 S - > E rop E  (rop是> < >= <=, ==, !=) ，优先级比not高保留产生式(0)， 优先级 <= not 保留规约式(1)
	deleteOperations.push_back(make_pair(37, make_pair("+", 0)));    //左结合保留归约式  
	deleteOperations.push_back(make_pair(37, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(37, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(37, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(37, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(37, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(37, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(37, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(37, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(37, make_pair("and", 0)));
	deleteOperations.push_back(make_pair(37, make_pair("or", 0)));
	deleteOperations.push_back(make_pair(38, make_pair("!=", 1)));   //38 状态 S - > E + E   ，优先级比+高保留产生式(0)， 优先级 <=+ 保留规约式(1)
	deleteOperations.push_back(make_pair(38, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(38, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(38, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(38, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(38, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(38, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(38, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(38, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(38, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(38, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(38, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("!=", 1)));   //39 状态 S - > E - E   ，优先级比+高保留产生式(0)， 优先级 <= - 保留规约式(1)
	deleteOperations.push_back(make_pair(39, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(39, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(39, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(39, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(39, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(39, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(39, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("!=", 1)));   //40 状态 S - > E * E   ，优先级比+高保留产生式(0)， 优先级 <= - 保留规约式(1)
	deleteOperations.push_back(make_pair(40, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(40, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(40, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(40, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(40, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("!=", 1)));   //41 状态 S - > E / E   ，优先级比/高保留产生式(0)， 优先级 <= /保留规约式(1)
	deleteOperations.push_back(make_pair(41, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(41, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(41, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(41, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(41, make_pair("or", 1)));

	//
	deleteOperations.push_back(make_pair(86, make_pair("!=", 0)));   //86 状态 S - > EA E  ，优先级比and高保留产生式， 优先级 <= and 保留规约式
	deleteOperations.push_back(make_pair(86, make_pair("+", 0)));    //左结合保留归约式
	deleteOperations.push_back(make_pair(86, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("<", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("<=", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("==", 0)));
	deleteOperations.push_back(make_pair(86, make_pair(">", 0)));
	deleteOperations.push_back(make_pair(86, make_pair(">=", 0)));
	deleteOperations.push_back(make_pair(86, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(86, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(87, make_pair("!=", 0)));   //87 状态 S - > E0 E  ，优先级比or高保留产生式(0)， 优先级 <= or 保留规约式(1)
	deleteOperations.push_back(make_pair(87, make_pair("+", 0)));    //左结合保留归约式
	deleteOperations.push_back(make_pair(87, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("<", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("<=", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("==", 0)));
	deleteOperations.push_back(make_pair(87, make_pair(">", 0)));
	deleteOperations.push_back(make_pair(87, make_pair(">=", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("and", 0)));
	deleteOperations.push_back(make_pair(87, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("!=", 1)));   //88 状态 S - > not E  ，优先级比not高保留产生式(0)， 优先级 <= not 保留规约式(1)
	deleteOperations.push_back(make_pair(88, make_pair("+", 1)));    //左结合保留归约式  
	deleteOperations.push_back(make_pair(88, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(88, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(88, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(88, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(89, make_pair("!=", 1)));   //89 状态 S - > E rop E  (rop是> < >= <=, ==, !=) ，优先级比not高保留产生式(0)， 优先级 <= not 保留规约式(1)
	deleteOperations.push_back(make_pair(89, make_pair("+", 0)));    //左结合保留归约式  
	deleteOperations.push_back(make_pair(89, make_pair("-", 0)));
	deleteOperations.push_back(make_pair(89, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(89, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(89, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(89, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(89, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(89, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(89, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(89, make_pair("and", 0)));
	deleteOperations.push_back(make_pair(89, make_pair("or", 0)));
	deleteOperations.push_back(make_pair(90, make_pair("!=", 1)));   //90 状态 S - > E + E   ，优先级比+高保留产生式(0)， 优先级 <=+ 保留规约式(1)
	deleteOperations.push_back(make_pair(90, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(90, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(90, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(90, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(90, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(90, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(90, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(90, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(90, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(90, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(90, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("!=", 1)));   //91 状态 S - > E - E   ，优先级比+高保留产生式(0)， 优先级 <= - 保留规约式(1)
	deleteOperations.push_back(make_pair(91, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(91, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("*", 0)));
	deleteOperations.push_back(make_pair(91, make_pair("/", 0)));
	deleteOperations.push_back(make_pair(91, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(91, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(91, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(91, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("!=", 1)));   //92 状态 S - > E * E   ，优先级比+高保留产生式(0)， 优先级 <= - 保留规约式(1)
	deleteOperations.push_back(make_pair(92, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(92, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(92, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(92, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(92, make_pair("or", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("!=", 1)));   //93状态 S - > E / E   ，优先级比/高保留产生式(0)， 优先级 <= /保留规约式(1)
	deleteOperations.push_back(make_pair(93, make_pair("+", 1)));    //左结合保留归约式  (1)
	deleteOperations.push_back(make_pair(93, make_pair("-", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("*", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("/", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("<", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("<=", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("==", 1)));
	deleteOperations.push_back(make_pair(93, make_pair(">", 1)));
	deleteOperations.push_back(make_pair(93, make_pair(">=", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("and", 1)));
	deleteOperations.push_back(make_pair(93, make_pair("or", 1)));
	myParser.sloveAmbiguousTable(deleteOperations);
	ofstream fout2 = ofstream();
	fout2.open(modelfile, ios::out);
	if (!fout2.is_open()) {
		cout << "无法打开模型文本" << endl;
		return false;
	}
	myParser.outParserModel(fout2);
	fout2.close();
    // 进行语法分析
	myParser.scanTokenStream(tokenstream, reportfile);
	system("pause");
	return 0;
}

/*
// 构造表达式，表达式定义的文法同 词法分析器 , 从表达式生成状态表
	set<string> nonTerminators = set<string>({ "S","A","B","S1" });
	set<string> terminators = set<string>({ "a","b","none","$","c","d" });
	vector<string> production0 = vector<string>({ "S1","S", });
	vector<string> production1 = vector<string>({ "S","A","a"});
	vector<string> production2 = vector<string>({ "S","b","A","c" });
	vector<string> production3 = vector<string>({ "S","B","c" });
	vector<string> production4 = vector<string>({ "S","b","B","a" });
	vector<string> production5 = vector<string>({ "A","d" });
	vector<string> production6 = vector<string>({ "B","d", });
	vector < vector<string>> productions = vector < vector<string>>(
		{
			production0,production1,production2,production3,production4,production5,production6
		});
*/