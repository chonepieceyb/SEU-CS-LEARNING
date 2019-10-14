package Bridge_pattern_1;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		//测试 
		//在 windows 上播放 mp4文件
		MP4File mp4File = new MP4File();
		WindowsPlayer windowsPlayer = new WindowsPlayer();
		windowsPlayer.setVedioFile( mp4File);
		windowsPlayer.play("视频1");
		
		//如果想要新增一个 平台 和一种播放格式 只需要创建一个新的类实现 VedioFile接口， 
		//新建一个类继承VedioPlayer类，不需要改变源代码
		FLVFile flvFile = new FLVFile();
		MacintoshPlayer mPlayer  = new MacintoshPlayer();
		mPlayer.setVedioFile( flvFile );
		mPlayer.play("视频2");
	}

}
