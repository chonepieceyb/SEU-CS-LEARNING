package HWCompany_simulate;

public class HWCompany {
	//由于华为公司只有一个 所以采用了 单例模式
	static private HWCompany instance;
	private HWRecruit hwRecruit;
	
	public void setHwRecruit(HWRecruit hwRecruit) {
		this.hwRecruit = hwRecruit;
	}
	private HWCompany() {
		
	}
	static public HWCompany getInstance() {
		if(instance ==null) {
			return new HWCompany();
		}else {
			return instance;
		}
	}
	public boolean hwRecruit(SeniorTalents st) {
		System.out.println("-------------------由华为公司总部直接进行的招聘-------------------------------");
		return this.hwRecruit.recruit(st);
	}
}
