package Adapter_pattern_1;

public class AdapterDogBird extends Robot {
	Bird bird;
	
	public void setBird(Bird bird) {
		this.bird = bird;
	}

	public void setDog(Dog dog) {
		this.dog = dog;
	}

	Dog dog;
	
	@Override
	public void cry() {
		// TODO 自动生成的方法存根
		this.bird.birdCry();
	}

	@Override
	public void run() {
		// TODO 自动生成的方法存根
		this.dog.run();
	}

}

