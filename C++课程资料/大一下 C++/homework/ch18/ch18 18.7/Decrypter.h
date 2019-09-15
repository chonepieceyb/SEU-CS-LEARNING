#pragma once
#ifndef DECRYPTER_H
#define DECRYPTER_H
#include<string>
#include<iostream>
#include"Encrypter.h"
using namespace std;
class Decrypter:public Encrypter
{
private:
	int i_mAntiKeystep;
public:
	Decrypter();
	Decrypter(const Encrypter&);
	void Decrypts(string&);
};
Decrypter::Decrypter()
{
	i_mAntiKeystep = 26 - getKeystep();
}
Decrypter::Decrypter(const Encrypter& t):Encrypter(t)
{
	i_mAntiKeystep = 26-getKeystep();
}
void Decrypter::Decrypts(string& t_sString)
{
	for (int i = 0;i < t_sString.size();i++)
	{
		if (t_sString[i] >= 'A'&&t_sString[i] <= 'Z')
		{
			int t_ichange = int(i_mAntiKeystep + int(t_sString[i]) - int('A') + 1);
			(t_ichange == 26 ? t_ichange = 26 : t_ichange %= 26);
			t_sString[i] = char('A' + t_ichange - 1);
		}
		else if (t_sString[i] >= 'a'&&t_sString[i] <= 'z')
		{
			int t_ichange = int(i_mAntiKeystep + int(t_sString[i]) - int('a') + 1);
			(t_ichange == 26 ? t_ichange = 26 : t_ichange %= 26);
			t_sString[i] = char('a' + t_ichange - 1);
		}
	}
	return;
}
#endif // !DECRYPTER_H;

