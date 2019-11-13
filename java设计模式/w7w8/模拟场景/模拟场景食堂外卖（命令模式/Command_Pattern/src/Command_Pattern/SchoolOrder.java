package Command_Pattern;

public class SchoolOrder extends Order {
	protected SchoolDiningHall dininghall;
	public void setDininghall(SchoolDiningHall dininghall) {
		this.dininghall = dininghall;
	}

	public SchoolOrder() {
		// TODO 自动生成的构造函数存根
		
	}
	public SchoolOrder(SchoolDiningHall dininghall) {
		// TODO 自动生成的构造函数存根
		this.setDininghall(dininghall);
	}

	@Override
	public void takeOutOrder() {
		// TODO 自动生成的方法存根
		System.out.println("学校食堂收到订单");
		this.dininghall.cook(this.orderName);
		System.out.println("学校食堂开始送外卖");
	}

}

