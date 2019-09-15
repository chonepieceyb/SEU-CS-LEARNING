#ifndef SAVEINGSACCOUNT_H
#define SAVEINGSACCOUNT_H
#include"Account.h"
using namespace std;
class SavingsAccount :public Account
{
public:
	SavingsAccount(const double = 0.0, const double = 0.0);
	double calculateInterest();
private:
	double m_d_interesRate;
};
#endif
