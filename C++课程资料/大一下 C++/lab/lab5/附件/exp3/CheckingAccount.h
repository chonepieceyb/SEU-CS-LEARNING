#ifndef CHECKING_H
#define CHECKING_H
#include"Account.h"
using namespace std;
class CheckingAccount :public Account
{
public:
	CheckingAccount(double, double);
	virtual void credit(const double);
	virtual void debit(const double);
	double getTransactionFee();
private:
	double m_d_transactionFee;
};
#endif
