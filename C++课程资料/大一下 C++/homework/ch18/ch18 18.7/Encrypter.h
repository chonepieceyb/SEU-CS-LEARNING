#pragma once
#ifndef ENCRYPTER_H
#define ENCRYPTER_H
#include<string>
#include<iostream>
using namespace std;
class Encrypter
{
private:
	int m_iKeystep;
protected:
	int getKeystep(void)
	{
		return m_iKeystep;
	}
public:
	Encrypter(int = 13);
	void encrypt(string&);
};
Encrypter::Encrypter(int t_iKeystep )
{
	m_iKeystep = t_iKeystep;
}
void Encrypter::encrypt(string& t_sString)
{
	for (int i = 0;i < t_sString.size();i++)
	{
		if (t_sString[i]>= 'A'&&t_sString[i] <='Z')
		{
			int t_ichange = int(m_iKeystep + int(t_sString[i])-int('A')+1);
			(t_ichange == 26 ? t_ichange = 26:t_ichange %= 26);
			t_sString[i] = char('A'+t_ichange-1);
		}
		else if (t_sString[i] >= 'a'&&t_sString[i] <= 'z')
		{
			int t_ichange = int(m_iKeystep + int(t_sString[i]) - int('a') + 1);
			(t_ichange == 26 ? t_ichange = 26 : t_ichange %= 26);
			t_sString[i] = char('a' + t_ichange - 1);
		}

	}
	return;
}
#endif // !ENCRYPTER_H
