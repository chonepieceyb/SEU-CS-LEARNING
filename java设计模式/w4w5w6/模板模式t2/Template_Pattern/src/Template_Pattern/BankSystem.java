package Template_Pattern;

public class BankSystem {
    //银行系统 客户端类
	// accountType 为了测试方便...  0 是 活期账户， 1 是死期账户
    public void inquireInterest(String username,String password, int accountType) {
    	// 验证用户，跳过
    	// 直接查询用户的账户类型，查数据库, 假设这里通过数据库获取了用户类型
    	 if (accountType==0) {
    		 CurrentAccount a = new CurrentAccount();
    		 a.process(username);
    	 }else if(accountType==1) {
    		 SavingAccount a = new  SavingAccount();
    		 a.process(username);
    	 }
    
    }
    

}
