package DecoratorPattern;

public class JarPhone extends PhoneDecorator {
	
	public JarPhone(Phone p ) {
		super(p);
	}
	@Override
	public void getCall() {
		// TODO 自动生成的方法存根
		this.phone.getCall();
		this.jar();
	}
	public void jar() {
		System.out.println("手机震动了");
	}
}

