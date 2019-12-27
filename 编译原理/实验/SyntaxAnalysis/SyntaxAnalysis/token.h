#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include"MarcoDef.h"
using namespace std;
class token
{
public:
	token();
	token(int t_id,string t_name, string v);
	~token();
	friend ostream& operator<<(ostream& output, const token& t);
	friend ofstream& operator<<(ofstream& foutput, const token& t);
	void generateTokenStream  (ofstream& fout);
	ATTRIBUTE_READ_ONLY(string, token_name);
	int getTokenID();
	ATTRIBUTE_READ_ONLY(string, value);
private:
	int token_id;
	string token_name;
	string value;
};


