#include "DFA.h"
#include "State.h"
#include "token.h"
#include<cctype>
#include<fstream>
string s5edgeJudge(string s) {
	if (s != "\"" || s == "digit" || s == "letter") {
		return "chars1";
	}
	else {
		return s;
	}
}
string s7edgeJudge(string s) {
	if (s != "'" || s =="digit" || s=="letter") {
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
	//############################################初始化模块

	//构造状态机
	int stateNum = 10; // 有10个状态
	string edges[] = { "_", "letter","digit",".", "\"","chars1","'","chars2" }; //chars1代表除了”之外的字符，chars2 代表除了‘之外的字符
	//申请一个2维数组,初始化为-1
	vector<int>** stateM = new vector<int>* [stateNum];
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
	string keepWords[] = { "if","else","while","(",")","+","-","*","/","def",":","return" ,",",";" ,"=" };
	for (int i = 0; i < 15; i++) {
		myDFA.addKeepWord(keepWords[i], 5 + i);
	}
	// 附加边判断函数
	myDFA.getState(7).setEdgeJudgeFunction(s7edgeJudge);
	myDFA.getState(5).setEdgeJudgeFunction(s5edgeJudge);
	
	//######################### 扫描文件模块
	ofstream fout = ofstream();
	ifstream fin = ifstream();
	fin.open("D:\\input.txt",ios::in);
	if (!fin.is_open()) {
		cout << "无法打开文件流" << endl;
		return 0;
	}
	fout.open("D:\\output.txt", ios::out);
	if (!fout.is_open()) {
		cout << "无法打开文件流" << endl;
		return 0;
	}
	string str;
	char c ;
	while (fin.get(c)) {
		if (c == ' ' || c == '\n'  ) {
			if (str == ""){
				continue;
			}
			token t = myDFA.scan(str, convertInput);
			t.generateTokenStream(fout);
			fout  << " ";
			str.clear();
			continue;
		}
		else {
			str+=c;
		}
	 } ;
	 token t = myDFA.scan(str, convertInput);
	 t.generateTokenStream(fout);
	 fout << t;
	fin.close();
	fout.close();
	//delete数组
	for (int i = 0; i < stateNum; i++) {
		if (stateM[i] != nullptr) {
			delete[] stateM[i];
		}
	}
	delete[] stateM;
	system("pause");
	return 0;
	
}



