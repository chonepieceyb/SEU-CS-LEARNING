package Command_Pattern;

public abstract class Order {
	protected String orderName;

	public void setOrderName(String orderName) {
		this.orderName = orderName;
	}
	
	public abstract void takeOutOrder();
}


