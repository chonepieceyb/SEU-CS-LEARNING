#include"SavingsAccount.h"
SavingsAccount::SavingsAccount(const double t_d_initialBalance, const double t_d_Rate) :Account(t_d_initialBalance), m_d_interesRate(t_d_Rate)
{}
double SavingsAccount::calculateInterest()
{
	double t_d_Interest = getbalance()*m_d_interesRate;
	setbalance(getbalance() + t_d_Interest);
	return t_d_Interest;
}