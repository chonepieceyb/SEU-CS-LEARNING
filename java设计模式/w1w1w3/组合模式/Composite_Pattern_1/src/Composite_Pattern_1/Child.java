package Composite_Pattern_1;

public class Child {
    //客户端类
	FruitElement fruits;
	public void setFruits(FruitElement fruits) {
		this.fruits = fruits;
	}
	public Child(FruitElement f) {
		this.fruits = f;
	}
	public void eatFruit() {
		System.out.println("孩子开始吃水果啦！\n");
		this.fruits.eat();
	}
}
