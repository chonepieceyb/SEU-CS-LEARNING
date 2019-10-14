package Mediator_Pattern;

public class Company extends Comunicator {

	public Company(Server s) {
		super(s);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void getMessage(String message) {
		// TODO 自动生成的方法存根
		System.out.println("电脑公司收到了消息:"+message);
	}
	public void answer(String message) {
		this.server.communicate(message, this);
	}

}

