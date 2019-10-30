package HWCompany_simulate;

import java.util.Scanner;

public class RealSocialRecruit implements SocialRecruit {
	// 真实招聘类
	@Override
	public boolean recruit(PersonalProfile file) {
		// TODO 自动生成的方法存根
		System.out.println("----------------进行社会招聘------------------------");
		file.printfile();
		System.out.println("请决定是否通过");
	    boolean issucess = test.sc.nextBoolean();
	    
		if (! issucess) {
			System.out.println("---------------很遗憾，没有通过社会招聘--------------------------");
			return issucess;
		}else {
			System.out.println("---------------恭喜你被华为公司录用了!--------------------------");
			return  issucess;
		}
	}
}
