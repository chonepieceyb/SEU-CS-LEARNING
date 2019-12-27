#pragma once
#include"ProductionManager.h"
#include"ParserState.h"
#include<iomanip>
#include"token.h"
#include<vector>
#include"SyntaxTree.h"
class BottomUpParser
{
	
public:
	BottomUpParser(set<string>terminators, set<string> nonTerminators, vector<vector<string>> productions,string begin="S1",string end="$",string none="none");
	virtual ~BottomUpParser();
	virtual void buildParserGraph() = 0;   //构造状态图
	virtual void buildParserTable() = 0;   //构造分析表
	virtual void printPaserTable(const int width=4,const int height =1)const;        //打印状态表
	virtual void outPaserTableAsFile (ofstream& fout, const int width = 4, const int height = 1)const;        //打印状态表
	virtual void outProductionsAsFile(ofstream& fout);        //打印产生式
	virtual void outParserModel(ofstream& fout) {};
	virtual bool scanTokenStream(vector<token> tokenstream , string analyze_report_dir );//从 tokenstream中进行语法分析，并且将分析报告（分析过程，语法树等）和分析模型（状态图，状态表输出到文件中）           
	vector<pair<string, int>> getOperations(int state, string input)const;
	static void printStack(vector<int> state_stack, vector<string> string_stack, vector<token> input, int begin);
	static void outputStackAsFile(ofstream& fout,vector<int> state_stack, vector<string> string_stack, vector<token> input ,int begin);
	Production getProductionById(int p_id); //通过 id返回唯一的表达式
	void sloveAmbiguousTable(vector< pair<int, pair<string, int>>> deleteOperations);
	ATTRIBUTE_MEMBER_FUNC(set<string>, nonTerminators);
	ATTRIBUTE_MEMBER_FUNC(set<string>, terminators);
	ATTRIBUTE_READ_ONLY(string, end);
	ATTRIBUTE_READ_ONLY(string, none);
	ATTRIBUTE_READ_ONLY(string, begin);
protected:
	string begin;
	string end;
	string none;
	set<string>terminators;           //终结符号，（包括$，一定）  ,不应该重复，
	set<string> nonTerminators;       //非终结节点，具体表现为分析表的纵坐标的值不应该重复，
	unordered_map<string,int> tableItems_map;           //分析表的纵坐标和int 对应的字典
	vector<string> tableItems;                           // 分析表的纵坐标， 和 map 互相映射
	vector<string> production_base_head;                    // base_head 和 base_id互相映射
	unordered_map<string, int> production_base_id;
	vector<vector<string>> string_productions;    //产生式
	vector<vector<vector<std::pair<string,int>>>> parserTable;     //分析表   pair第一个表示 类型 s 转移,r规约， int 表示目标
	ProductionManager pm;                    //所有的节点都保存在pm中
};

