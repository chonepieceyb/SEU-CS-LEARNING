package Template_Pattern;

public class CurrentAccount extends Account {

	@Override
	public double calInterest(double capital) {
		// TODO 自动生成的方法存根
		// 利息计算不同
		System.out.println("该账户是活期账户，采用活期账户利息计算方法");
		return capital*0.01;
				
	}

}
