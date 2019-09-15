#ifndef ACCOUNT_H
#define ACCOUNT_H
#include<iostream>
using namespace std;
class Account
{
public:
	Account(const double);
	virtual void credit(const double);
	virtual void debit(const double);
	double getbalance(void)const
	{
		return m_d_balance;
	}
	void setbalance(const double t_d_amount = 0.0)
	{
		if (t_d_amount >= 0.0)
			m_d_balance = t_d_amount;
		else
		{
			cout << "The initiate balance is invalid, the balance is set to 0.0\n";
			m_d_balance = 0.0;
		}
	}
private:
	double m_d_balance;
};
#endif
