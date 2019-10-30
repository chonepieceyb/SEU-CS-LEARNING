package Template_Pattern;

public abstract class Account {
	
     // 基本方法 具体方法， 查账用户信息，返回用户本金
     final public  double  getCapital(String username) {
    	 //插叙数据库，参数可以是 username 或者 uuid 根据具体情况而定，这里用username
    	 
    	 //本金默认返回 100
    	 return 100.0;
     }
     
     // 基本方法 抽象方法， 由本金计算利息 由子类实现
     abstract public double calInterest(double capital);
     
     //基本方法 具体方法，打印利息
     final public void printInterest(double interest) {
    	 System.out.println("利息为:"+interest);
     }
     
     //模板方法， 整个个流程
     public void  process(String username) {

    	 // 获取本金
    	 Double capital =  getCapital(username);
    	 
    	 //计算利息
    	 Double interest = calInterest(capital);
    	 
    	 //打印利息
    	 printInterest(interest);
     }
}

