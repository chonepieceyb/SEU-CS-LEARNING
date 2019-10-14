package Mediator_Pttern_2;

public abstract class Comunicator {
	protected Server server;
	protected String key;
	public Comunicator(String key){
		this.key = key;
	}
	public String getKey() {
		return this.key;
	}
	public void setKey(String key) {
		this.key = key;
	}
	public void setServer(Server server) {
		this.server = server;
	}
	public abstract void getMessage(String message,String from);
}
