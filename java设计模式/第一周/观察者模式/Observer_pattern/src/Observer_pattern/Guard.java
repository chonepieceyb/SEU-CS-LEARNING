package Observer_pattern;

public class Guard implements CustomerListener {
	
	public void comeToSpot() {
		System.out.println("保安赶到现场");
	}
	@Override
	public void response() {
		// TODO 自动生成的方法存根
		this.comeToSpot();
	}

}
