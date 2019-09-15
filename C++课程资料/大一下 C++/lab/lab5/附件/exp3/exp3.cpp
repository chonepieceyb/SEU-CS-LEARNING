#include<iostream>
#include<iomanip>
#include"Account.h"
#include"SavingsAccount.h"
#include"CheckingAccount.h"
#include<vector>
#include<typeinfo>
using namespace std;
int main()
{
	/*double t_d_temp;
	SavingsAccount m_SAcc_account1(25.00,0.03);
	cout<<"Account 1 balance: $"<<setprecision(4)<<m_SAcc_account1.getbalance()<<endl;
	cout<<"Enter an amount to withdraw from Account 1: ";
	cin>>t_d_temp;
	m_SAcc_account1.debit(t_d_temp);
	cout<<"Enter an amount to deposit into Account 1: ";
	cin>>t_d_temp;
	m_SAcc_account1.credit(t_d_temp);
	cout<<"Adding $"<<m_SAcc_account1.calculateInterest()<<"interest to Account 1(a SavingsAccount)\n";
	cout<<"Updated Account 1 balance: $"<<setprecision(4)<<m_SAcc_account1.getbalance()<<"\n";*/
	vector<Account*> m_Acc_accounts(4);
	m_Acc_accounts[0] = new SavingsAccount(25.00, 0.03);
	m_Acc_accounts[1] = new CheckingAccount(80.00, 1.00);
	m_Acc_accounts[2] = new SavingsAccount(200.00, 0.015);
	m_Acc_accounts[3] = new CheckingAccount(400.00, 0.50);
	for (int i = 0;i < 4;i++)
	{
		if (dynamic_cast<SavingsAccount*>(m_Acc_accounts[i]) != 0)
		{
			SavingsAccount* t_ptr_savings = dynamic_cast<SavingsAccount*>(m_Acc_accounts[i]);
			double t_d_temp;
			cout << typeid(*t_ptr_savings).name() << i + 1 << " balance: $" << t_ptr_savings->getbalance() << endl;
			cout << "Enter an amount to withdraw from " << typeid(*t_ptr_savings).name() << i + 1<<":";
			cin >> t_d_temp;
			t_ptr_savings->debit(t_d_temp);
			cout << "Enter an amount to deposit into " << typeid(*t_ptr_savings).name() << i + 1 << ":";;
			cin >> t_d_temp;
			t_ptr_savings->credit(t_d_temp);
			cout << "Adding $" << t_ptr_savings->calculateInterest() << " interest to " << typeid(*t_ptr_savings).name() << i + 1 << "(a SavingsAccount)\n";
			cout << "Updated"<< typeid(*t_ptr_savings).name() << i + 1 << " balance: $"  << t_ptr_savings->getbalance() << "\n\n";
		}
		if (dynamic_cast<CheckingAccount*>(m_Acc_accounts[i]) != 0)
		{
			CheckingAccount* t_ptr_checkings = dynamic_cast<CheckingAccount*>(m_Acc_accounts[i]);
			double t_d_temp;
			cout << typeid(*t_ptr_checkings).name() << i + 1 << " balance: $"  << t_ptr_checkings->getbalance() << endl;
			cout << "Enter an amount to withdraw from " << typeid(*t_ptr_checkings).name() << i + 1 << ":";;
			cin >> t_d_temp;
			t_ptr_checkings->debit(t_d_temp);
			cout << "$" << t_ptr_checkings->getTransactionFee() << " transaction fee charged\n";
			cout << "Enter an amount to deposit into " << typeid(*t_ptr_checkings).name() << i + 1 << ":";;
			cin >> t_d_temp;
			t_ptr_checkings->credit(t_d_temp);
			cout << "$" << t_ptr_checkings->getTransactionFee() << " transaction fee charged\n";
			cout << "Updated "<< typeid(*t_ptr_checkings).name() << i + 1 <<" balance: $"  << t_ptr_checkings->getbalance() << "\n\n";
		}
	}
		return 0;
	}