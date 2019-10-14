package Mediator_Pttern_2;

public class SHDJCompany extends Comunicator {

	public SHDJCompany(String key) {
		super(key);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void getMessage(String message, String from) {
		// TODO 自动生成的方法存根
		System.out.println("上海大金公司收到 "+from +"的消息： "+message);
	}
	public void replay(String message,String to) {
		this.server.communicate(message, this.getKey(), to);
	}
}
