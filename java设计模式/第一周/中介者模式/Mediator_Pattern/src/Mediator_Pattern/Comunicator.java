package Mediator_Pattern;

public abstract class Comunicator {
	Server server;
	public  Comunicator(Server s ) {
		this.server = s;
	}
	public abstract void getMessage(String message);
	
}
