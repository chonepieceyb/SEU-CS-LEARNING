package dapter_pattern_3;

public class CatDogAdapter implements CatBehavior, DogBehavior {
	CatBehavior cat;
	public void setCat(CatBehavior cat) {
		this.cat = cat;
	}

	public void setDog(DogBehavior dog) {
		this.dog = dog;
	}

	DogBehavior dog;
	
	public CatDogAdapter(CatBehavior c,DogBehavior d) {
		// TODO 自动生成的构造函数存根
		this.cat = c;
		this.dog = d;
	}

	@Override
	public void wang() {
		// TODO 自动生成的方法存根
		this.cat.catchMouse();
	}

	@Override
	public void catchMouse() {
		// TODO 自动生成的方法存根
		this.dog.wang();
	}

}
