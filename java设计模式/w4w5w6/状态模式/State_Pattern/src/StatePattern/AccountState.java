package StatePattern;

public abstract class AccountState {
	Account account;
	double balance;
	public AccountState(double balance, Account a ) {
		// TODO 自动生成的构造函数存根
		this.account = a;
		this.balance= balance;
	}
	public abstract void  changeState();
	public void withdraw(double amount) {
		//取款函数
		this.balance -= amount;
		System.out.println("成功取款 "+amount+" 元");
		System.out.println("余额为 "+this.balance+" 元");
		changeState();
	}
	public void deposit(double amount) {
		this.balance += amount;
		System.out.println("成功存款 "+amount+" 元");
		System.out.println("余额为 "+this.balance+" 元");
		changeState();
	}
}


