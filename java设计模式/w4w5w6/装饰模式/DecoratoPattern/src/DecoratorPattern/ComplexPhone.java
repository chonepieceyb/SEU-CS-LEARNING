package DecoratorPattern;

public class ComplexPhone extends PhoneDecorator {

	public ComplexPhone(Phone p) {
		super(p);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void getCall() {
		// TODO 自动生成的方法存根
		this.phone.getCall();
		this.light();
	}
	public void light() {
		System.out.println("手机来电发光了");
	}
}


