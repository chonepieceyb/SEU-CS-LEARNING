package DiningHallSimulate;

public class Student implements Visitor {
	private String name;
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public PayMethod getPayMethod() {
		return payMethod;
	}
	public void setPayMethod(PayMethod payMethod) {
		this.payMethod = payMethod;
	}

	private PayMethod payMethod;
	public String wishFood=null;
	
	public Student(String name) {
		this.name=name;
	}
	@Override
	public void visit(HangMenJi f) {
		// TODO 自动生成的方法存根
		System.out.println("学生点了"+f.getName());
		this.pay(f.price);
	}

	@Override
	public void visit(DiaoZhaBing f) {
		// TODO 自动生成的方法存根
		System.out.println("学生点了"+f.getName());
		this.pay(f.price);
	}

	@Override
	public void visit(NiuRouMian f) {
		// TODO 自动生成的方法存根
		System.out.println("学生点了"+f.getName());
		this.pay(f.price);
	}
	
	//点餐函数
	public String takeOrder() {
		//这个函数从学生出获得想要吃的食物的名称...这里假设从类里的一个变量获得，这个变量可以随便指定
		return this.wishFood;
	}
	//付钱
	public void pay(Double d) {
		this.payMethod.pay(d);
	}
}
