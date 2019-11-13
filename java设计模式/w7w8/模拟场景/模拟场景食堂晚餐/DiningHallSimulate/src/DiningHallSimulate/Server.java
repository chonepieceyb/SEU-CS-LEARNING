package DiningHallSimulate;

public class Server implements Visitor {
	//食堂工作人员类
	@Override
	public void visit(HangMenJi f) {
		// TODO 自动生成的方法存根
		System.out.println("食堂工作人员打了"+f.getName());
	}

	@Override
	public void visit(DiaoZhaBing f) {
		// TODO 自动生成的方法存根
		System.out.println("食堂工作人员打了"+f.getName());
	}

	@Override
	public void visit(NiuRouMian f) {
		// TODO 自动生成的方法存根
		System.out.println("食堂工作人员打了"+f.getName());
	}

}
