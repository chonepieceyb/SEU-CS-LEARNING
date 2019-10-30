package Mediator_Pattern;

public class Customer extends Comunicator {
	public Customer(Server s){
		super(s);
	}
	@Override
	public void getMessage(String message) {
		// TODO 自动生成的方法存根
		System.out.println("客户收到了消息："+message);
	}
	public void ask(String message) {
		this.server.communicate(message, this);
	}
}
