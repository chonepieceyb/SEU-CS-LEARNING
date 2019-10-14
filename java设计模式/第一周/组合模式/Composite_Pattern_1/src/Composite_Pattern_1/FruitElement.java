package Composite_Pattern_1;

public abstract class FruitElement {
	public abstract void add(FruitElement c);
	public abstract void remove(FruitElement c);
	public abstract FruitElement getChild(int index);
	public abstract void eat();
}

