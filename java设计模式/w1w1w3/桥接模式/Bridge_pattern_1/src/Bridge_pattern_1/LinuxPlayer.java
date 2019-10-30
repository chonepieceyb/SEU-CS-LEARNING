package Bridge_pattern_1;

public class LinuxPlayer extends VedioPlayer {

	@Override
	public void play(String fileName) {
		// TODO 自动生成的方法存根
		this.vedioFile.decode(fileName);
		System.out.println("在Linux平台播放");
	}

}
