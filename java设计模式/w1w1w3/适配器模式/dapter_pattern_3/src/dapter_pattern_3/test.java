package dapter_pattern_3;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		Cat cat = new Cat();
		Dog dog = new Dog();
		CatDogAdapter adapter = new CatDogAdapter(cat,dog);
		adapter.catchMouse();   //猫像狗一样叫
		adapter.wang();         //狗像猫一样抓老鼠
	}

}

