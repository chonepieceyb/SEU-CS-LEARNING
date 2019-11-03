package DecoratorPattern;

public abstract class PhoneDecorator extends Phone {
	protected Phone phone;

	public PhoneDecorator(Phone p ) {
		this.phone = p;
	}

	abstract public void getCall() ;
}


