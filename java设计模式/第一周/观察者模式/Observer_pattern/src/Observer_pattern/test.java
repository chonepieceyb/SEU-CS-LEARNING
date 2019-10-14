package Observer_pattern;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
	    RudeCustomer customer = new RudeCustomer();
	    Server server = new Server();
	    Guard guard = new Guard();
	    customer.attach(server);
	    customer.attach(guard);
	    customer.shout();
	}

}
