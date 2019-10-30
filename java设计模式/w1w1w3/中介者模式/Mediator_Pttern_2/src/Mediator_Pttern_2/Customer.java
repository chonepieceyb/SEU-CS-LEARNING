package Mediator_Pttern_2;

public class Customer extends Comunicator {
	public Customer (String key){
		super(key);
	}
	@Override
	public void getMessage(String message,String from) {
		// TODO 自动生成的方法存根
		System.out.println("消费者收到 "+from +"的回复： "+message);
	}
	public void ask(String message,String to) {
		this.server.communicate(message, this.getKey(), to);
	}

}
