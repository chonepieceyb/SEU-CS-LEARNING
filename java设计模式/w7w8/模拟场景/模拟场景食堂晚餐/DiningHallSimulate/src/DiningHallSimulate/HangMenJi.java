package DiningHallSimulate;

public class HangMenJi extends Food {

	public HangMenJi(Double price, String name) {
		super(price, name);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void accept(Visitor v) {
		// TODO 自动生成的方法存根
		v.visit(this);
	}

}
