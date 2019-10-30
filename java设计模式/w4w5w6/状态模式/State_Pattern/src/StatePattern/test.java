package StatePattern;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		// 客户端类
		
		Account myAccount = new Account("chonepieceyb",1000);
		myAccount.withdraw(500);
		myAccount.withdraw(1000);
		myAccount.withdraw(1000);
		myAccount.withdraw(1000);
		myAccount.deposit(5000);
		myAccount.withdraw(2000);
	}

}


