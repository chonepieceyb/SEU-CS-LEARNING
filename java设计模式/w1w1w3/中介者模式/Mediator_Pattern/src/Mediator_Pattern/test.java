package Mediator_Pattern;

public class test {


	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		CustomerServer server = new CustomerServer();

		Customer customer = new Customer(server);
		Company company = new Company(server);
		server.setCompany(company);
		server.setCustomer(customer);
		customer.ask("我买的电脑用不了");
		company.answer("把电源接上就能用了");
	}

}

