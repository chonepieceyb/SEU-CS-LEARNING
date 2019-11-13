package DiningHallSimulate;

import java.util.ArrayList;

import DiningHallSimulate.SeatList.SeatIterator;

public abstract class DiningHall {
	protected ArrayList<Window> windows = new ArrayList<Window>();
	protected SeatIterator  seats;
	public void setSeats(SeatIterator seats) {
		this.seats = seats;
	}
	public void addSeat(Seat s) {
		this.seats.addSeat(s);
	}
	public void addWindow(Window w) {
		this.windows.add(w);
	}
    abstract public Seat findSeat();
	public abstract void lineup(int windownumber,Student s);
	public abstract void process();
}
