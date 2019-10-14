package Composite_Pattern_2;

public class TextFileScan extends AntiComponent {
	
	String fileName;
	public TextFileScan(String f) {
		// TODO 自动生成的构造函数存根
		this.fileName = f;
	}
	@Override
	public void scan() {
		// TODO 自动生成的方法存根
		System.out.println("扫描了文本文件: "+this.fileName);
	}

}

