package Mediator_Pttern_2;

import java.util.HashMap;

public class NJDJServer extends Server {

	private HashMap<String,Comunicator> comunicators = new HashMap<String,Comunicator>();
	public void addComunicator(Comunicator c) {
		this.comunicators.put(c.getKey(), c);
	}
	public void removeComunicator(String key) {
		this.comunicators.remove(key);
	}
	@Override
	public void communicate(String message, String from, String to) {
		// TODO 自动生成的方法存根
		if(this.comunicators.get(to)!=null) {
			this.comunicators.get(to).getMessage(message,from);
		}
	}

}
