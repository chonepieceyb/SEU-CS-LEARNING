package DiningHallSimulate;

public abstract class Food {
	protected Double price;
	public Double getPrice() {
		return price;
	}
	public String getName() {
		return name;
	}
	protected String name;
	public Food(Double price,String name) {
		this.price = price;
		this.name = name;
	}
	abstract public void accept(Visitor v);
}
