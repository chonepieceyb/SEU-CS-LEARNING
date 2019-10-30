package Composite_Pattern_1;

import java.util.ArrayList;

public class FruitPlate extends FruitElement {
	ArrayList<FruitElement> fruitElements = new ArrayList<FruitElement>();
	@Override
	public void add(FruitElement c) {
		// TODO 自动生成的方法存根
		this.fruitElements.add(c);
	}

	@Override
	public void remove(FruitElement c) {
		// TODO 自动生成的方法存根
		this.fruitElements.remove(c);
	}

	@Override
	public FruitElement getChild(int index) {
		// TODO 自动生成的方法存根
		return this.fruitElements.get(index);
	}

	@Override
	public void eat() {
		// TODO 自动生成的方法存根
		System.out.println("开始吃果盘里的水果");
		for(FruitElement f:this.fruitElements ) {
			f.eat();
		}
	}

}
