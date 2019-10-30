package StatePattern;

public class YellowState extends AccountState {

	public YellowState(double balance, Account a) {
		super(balance, a);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void changeState() {
		// TODO 自动生成的方法存根
		if (this.balance>=0) {
			this.account.setAccountState(new GreenState(this.balance,this.account));
		}else if (this.balance<-1000) {
			this.account.setAccountState(new RedState(this.balance,this.account));
		}
	}

}


