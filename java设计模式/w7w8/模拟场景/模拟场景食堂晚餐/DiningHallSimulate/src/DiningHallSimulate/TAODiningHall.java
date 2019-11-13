package DiningHallSimulate;

public class TAODiningHall extends DiningHall {

	@Override
	public Seat findSeat() {
		// TODO 自动生成的方法存根
		Seat s = this.seats.getEmptySeat();
		if(s == null ) {
			System.out.println("没座位了");
			return null;
		}
		return s;
	}

	@Override
	public void lineup(int windownumber,Student s) {
		// TODO 自动生成的方法存根
		if(windownumber>= this.windows.size()) {
			System.out.println("没有这个窗口");
			return;
		}
		this.windows.get(windownumber).addStudent(s);
	}

	@Override
	public void process() {
		// TODO 自动生成的方法存根
		// 调用每个窗口的process函数
		int i =0;
		for(Window w:this.windows) {
			System.out.println("窗口"+i+"工作中");
			w.process();
			i++;
		}
	}

}
