package DiningHallSimulate;

abstract public class DiningHallDecorator extends DiningHall {
	protected DiningHall dininghall;
	 DiningHallDecorator(DiningHall dininghall){
		 this.dininghall = dininghall;
	 }
}
