package Composite_Pattern_2;

import java.util.ArrayList;

public class FolderScan extends AntiComponent {
	ArrayList<AntiComponent> antis = new ArrayList<AntiComponent>();
	
	public  void add(AntiComponent c) {
		antis.add(c);
	}
	public void remove(AntiComponent c) {
		antis.remove(c);
	}
	public AntiComponent findChild(int index) {
		return antis.get(index);
	}
	@Override
	public void scan() {
		// TODO 自动生成的方法存根
		System.out.println("开始扫描文件夹");
		for(AntiComponent a: antis) {
			a.scan();
		}
	}

}
