package HWCompany_simulate;

public abstract class CampusRecruit implements Recruit {
	//采用 职责链模式，校园招聘类
	private CampusRecruit nextRecruit;

	public CampusRecruit getNextRecruit() {
		return nextRecruit;
	}

	public void setNextRecruit(CampusRecruit nextRecruit) {
		this.nextRecruit = nextRecruit;
	}
}
