package Composite_Pattern_1;

public class Peer extends FruitElement {

	@Override
	public void add(FruitElement c) {
		// TODO 自动生成的方法存根
		System.out.println("添加出现错误");
	}

	@Override
	public void remove(FruitElement c) {
		// TODO 自动生成的方法存根
		System.out.println("删除出现错误");
	}

	@Override
	public FruitElement getChild(int index) {
		// TODO 自动生成的方法存根
		System.out.println("获取子节点出现错误");
		return null;
	}

	@Override
	public void eat() {
		// TODO 自动生成的方法存根
		System.out.println("吃了一个梨");

	}

}
