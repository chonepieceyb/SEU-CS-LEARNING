package DiningHallSimulate;

public class MEIDiningHall extends DiningHallDecorator {

	public MEIDiningHall(DiningHall dininghall) {
		super(dininghall);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public Seat findSeat() {
		// TODO 自动生成的方法存根
		System.out.println("梅园的椅子更加舒适");
		return this.dininghall.findSeat();
	}

	@Override
	public void lineup(int windownumber, Student s) {
		// TODO 自动生成的方法存根
		this.dininghall.lineup(windownumber, s);
	}

	@Override
	public void process() {
		// TODO 自动生成的方法存根
		System.out.println("梅园的饭菜更加可口，服务更好，打的菜更多");
		this.dininghall.process();
	}

}
