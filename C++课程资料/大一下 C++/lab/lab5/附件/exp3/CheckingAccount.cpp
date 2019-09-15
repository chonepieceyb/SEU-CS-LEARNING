#include"CheckingAccount.h"
CheckingAccount::CheckingAccount(double t_d_initialBalance, double t_d_Fee) :Account(t_d_initialBalance), m_d_transactionFee(t_d_Fee)
{}
void CheckingAccount::credit(const double t_d_credit)
{
	if (t_d_credit >= m_d_transactionFee)
		Account::credit(t_d_credit - m_d_transactionFee);
	else
		Account::debit( m_d_transactionFee-t_d_credit);
}
void CheckingAccount::debit(const double t_d_debit)
{
	Account::debit(t_d_debit + m_d_transactionFee);
}
double CheckingAccount:: getTransactionFee()
{
	return  m_d_transactionFee;
}