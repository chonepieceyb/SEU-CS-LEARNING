package Composite_Pattern_2;

public class ImageFileScan extends AntiComponent {

	String fileName;
	public ImageFileScan(String f) {
		// TODO 自动生成的构造函数存根
		this.fileName = f;
	}
	@Override
	public void scan() {
		// TODO 自动生成的方法存根
		System.out.println("扫描了图片: "+this.fileName);
	}

}

