package Command_Pattern;

public class Student {
	protected Order order;

	public void setOrder(Order order) {
		this.order = order;
	}
	public Student( Order order){
		this.setOrder(order);
	}
	public Student() {
		
	}
	public void makeOrder(String orderName) {
		this.order.setOrderName(orderName);
		this.order.takeOutOrder();   //´øÍâÂô
	}
}


