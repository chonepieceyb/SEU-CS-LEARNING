package Composite_Pattern_2;

public abstract class AntiComponent {
	public  void add(AntiComponent c) {
		System.out.println("添加出现问题了");
	}
	public void remove(AntiComponent c) {
		System.out.println("删除出现问题了");
	}
	public AntiComponent findChild(int index) {
		System.out.println("删除出现问题了");
		return null;
	}
	public abstract void scan();
}

