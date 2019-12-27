#pragma once
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class token
{
public:
	token(int t_id,string t_name, string v);
	~token();
	friend ostream& operator<<(ostream& output, const token& t);
	friend ofstream& operator<<(ofstream& foutput, const token& t);
	void generateTokenStream  (ofstream& fout);
	int getTokenID();
private:
	int token_id;
	string token_name;
	string value;
};


