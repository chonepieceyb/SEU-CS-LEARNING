package HWCompany_simulate;

public class HWRecruitAdapter implements SocialRecruit {
	//由于接口不同，这里使用了 适配器模式 适配华为公司和社招的接口
	private HWCompany HUAWEI;
	public void setHUAWEI(HWCompany hw) {
		this.HUAWEI= hw;
	}
	@Override
	public boolean recruit(PersonalProfile file) {
		// TODO 自动生成的方法存根
		Interviewee i = file.getInterviewee();
		if( i instanceof SeniorTalents) {
			System.out.println("-------------------对于高级人才将由华为公司总部直接进行的招聘-------------------------------");
			return this.HUAWEI.hwRecruit((SeniorTalents)i);
		}else {
			System.out.println("---------对不起华为公司目前需要发表论文数较多，取得一定学术成果的高级人才,您不符合条件，请通过其它的方式进入华为公司----------------------------------------------");
			return false;
		}
	}
}
