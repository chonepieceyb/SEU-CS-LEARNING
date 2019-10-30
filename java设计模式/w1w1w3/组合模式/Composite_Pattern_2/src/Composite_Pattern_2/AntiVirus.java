package Composite_Pattern_2;

public class AntiVirus {
	AntiComponent anti;
	public void setAnti(AntiComponent anti) {
		this.anti = anti;
	}
	public AntiVirus(AntiComponent a){
		this.anti = a;
	}
	public void scanVirus() {
		System.out.println("开始进行病毒扫描！\n");
		this.anti.scan();
	}
}
