package StatePattern;

public class GreenState extends AccountState {

	public GreenState(double balance, Account a) {
		super(balance, a);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void changeState() {
		// TODO 自动生成的方法存根
		if (this.balance<0 && this.balance >=-1000) {
			this.account.setAccountState(new YellowState(this.balance,this.account));
		}else if (this.balance<-1000) {
			this.account.setAccountState(new RedState(this.balance,this.account));
		}
	}

}


