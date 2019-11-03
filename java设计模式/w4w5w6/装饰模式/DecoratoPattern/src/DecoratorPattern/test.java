package DecoratorPattern;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		//测试类
		SimplePhone sp = new SimplePhone();
		sp.getCall();
		System.out.println("-----------------------------------");
		JarPhone jp= new JarPhone(sp);  //第一次升级
		jp.getCall();
		System.out.println("-----------------------------------");
		ComplexPhone cp = new ComplexPhone(jp); //第二次升级
		cp.getCall();
	}

}

