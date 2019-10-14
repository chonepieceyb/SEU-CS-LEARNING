package Observer_pattern;

import java.util.ArrayList;

public abstract class Customer {

	ArrayList<CustomerListener> listener = new ArrayList<CustomerListener>();
	public void attach(CustomerListener l) {
		listener.add(l);
	}
	public void dettach(CustomerListener l) {
		listener.remove(l);
	}
	public abstract void catchAttention();

}
