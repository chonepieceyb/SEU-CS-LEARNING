package DiningHallSimulate;

public abstract class WindowDecorator extends Window {
	protected Window window;
	public WindowDecorator(Window w){
		this.window = w;
	}
}
