package Observer_pattern;

public class Server implements CustomerListener {

	public void beScared() {
		System.out.println("客服受到惊吓");
	}

	@Override
	public void response() {
		// TODO 自动生成的方法存根
		 this.beScared();
	}

}
