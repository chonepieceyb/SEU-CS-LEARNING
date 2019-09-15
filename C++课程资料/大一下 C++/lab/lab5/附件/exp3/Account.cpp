#include"Account.h"
Account::Account(const double t_d_balance)
{
	setbalance(t_d_balance);
}
void Account::credit(const double t_d_credit)
{
	setbalance(getbalance() + t_d_credit);
}
void Account::debit(const double t_d_debit)
{
	if (getbalance() - t_d_debit >= 0.0)
		setbalance(getbalance() - t_d_debit);
	else
		cout << "Debit amount exceeded account balance.\n";
}