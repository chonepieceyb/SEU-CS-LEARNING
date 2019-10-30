package StatePattern;

public class Account {
	AccountState  accountState;
	public void setAccountState(AccountState accountState) {
		this.accountState = accountState;
	}
	String username;
	Account(String user, double balance ){
		this.username = user;
		this.accountState = new GreenState(balance,this);
	}
	public void withdraw(double amount) {
		//取款函数
		System.out.println(this.username+" 欢迎！！！");
		this.accountState.withdraw(amount);
	}
	public void deposit(double amount) {
		//存款函数
		System.out.println(this.username+" 欢迎！！！");
		this.accountState.deposit(amount);
	}
}
