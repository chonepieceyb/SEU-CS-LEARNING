package HWCompany_simulate;

public class ProxyCompany implements SocialRecruit {
	//代理公司类 使用了代理模式
	private RealSocialRecruit  realSocialRecruit;
	public void setRealSocialRecruit(RealSocialRecruit realSocialRecruit) {
		this.realSocialRecruit = realSocialRecruit;
	}
	public String getCompanyname() {
		return companyname;
	}
	public void setCompanyname(String companyname) {
		this.companyname = companyname;
	}
	public String companyname;
	public ProxyCompany (String companyname) {
		this.companyname = companyname;
	}
	@Override
	public boolean recruit(PersonalProfile file) {
		// TODO 自动生成的方法存根
		System.out.println("------------------华为公司委托 "+ this.companyname +" 进行社会招聘----------------------------------");
		return this.realSocialRecruit.recruit(file);
	}
}
