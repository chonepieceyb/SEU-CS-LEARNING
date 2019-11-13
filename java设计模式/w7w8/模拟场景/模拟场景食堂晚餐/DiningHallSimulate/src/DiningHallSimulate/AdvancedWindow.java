package DiningHallSimulate;

public class AdvancedWindow extends WindowDecorator {

	public AdvancedWindow(Window w) {
		super(w);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void process() {
		// TODO 自动生成的方法存根
		System.out.println("窗口前有显示所有菜品的LED屏幕");
		this.window.process();
	}

}
