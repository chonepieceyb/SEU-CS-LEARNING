package Mediator_Pttern_2;

public class SNCompany extends Comunicator {

	public SNCompany(String key) {
		super(key);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void getMessage(String message, String from) {
		// TODO 自动生成的方法存根
		System.out.println("苏宁公司收到 "+from +"的询问： "+message);
	}
	public void replay(String message,String to) {
		this.server.communicate(message, this.getKey(), to);
	}
}
