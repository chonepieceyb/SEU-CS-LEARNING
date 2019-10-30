package Template_Pattern;

public class SavingAccount extends Account {

	@Override
	public double calInterest(double capital) {
		// TODO 自动生成的方法存根
		System.out.println("该账户是定期账户，采用定期账户利息计算方法");
		return capital*0.03;
	}

}
