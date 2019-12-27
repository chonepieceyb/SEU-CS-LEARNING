#include"token.h"

token::token(int t_id, string t_name, string v):token_id(t_id),token_name(t_name),value(v)
{
}


token::~token()
{
}
int token::getTokenID() {
	return token_id;
}
ostream& operator<<(ostream& output, const token& t) {
	output << '(' << t.token_id << ',' << t.token_name << ',' << t.value << ')';
	return output;
}
ofstream& operator<<(ofstream& foutput, const token& t) {
	foutput << '(' << t.token_id << ',' << t.token_name << ',' << t.value << ')';
	return foutput;
}
void token::generateTokenStream(ofstream& fout) {
	fout << token_name << " "<<value;
}