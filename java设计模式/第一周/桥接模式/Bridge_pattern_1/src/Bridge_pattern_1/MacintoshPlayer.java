package Bridge_pattern_1;

public class MacintoshPlayer extends VedioPlayer {

	@Override
	public void play(String fileName) {
		// TODO 自动生成的方法存根
		this.vedioFile.decode(fileName);
		System.out.println("在Macintosh平台播放");

	}

}
