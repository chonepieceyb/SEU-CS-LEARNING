package Observer_pattern;

public class RudeCustomer extends Customer {


	@Override
	public void catchAttention() {
		// TODO 自动生成的方法存根
		for ( CustomerListener l: this.listener) {
			l.response();
		}
	}
	public void shout() {
		System.out.println("顾客大声说话");
		catchAttention();
	}
}
