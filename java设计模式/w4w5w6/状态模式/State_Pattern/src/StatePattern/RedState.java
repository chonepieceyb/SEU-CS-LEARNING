package StatePattern;

public class RedState extends AccountState {

	public RedState(double balance, Account a) {
		super(balance, a);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void changeState() {
		// TODO 自动生成的方法存根
		if (this.balance>=0) {
			this.account.setAccountState(new GreenState(this.balance,this.account));
		}else if (this.balance>=-1000 && this.balance<0) {
			this.account.setAccountState(new YellowState(this.balance,this.account));
		}
	}
	public void withdraw(double amount) {
		System.out.println("当前账户为透支状态，无法取款只能存款！");
	}

}


