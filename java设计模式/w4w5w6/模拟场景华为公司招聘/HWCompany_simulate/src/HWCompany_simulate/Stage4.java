package HWCompany_simulate;

import java.util.Scanner;

public class Stage4 extends CampusRecruit {
	//华为校招终审类
	@Override
	public boolean recruit(PersonalProfile file) {
		// TODO 自动生成的方法存根
		System.out.println("----------------进入华为终选------------------------");
		file.printfile();
		System.out.println("请决定是否通过");
	    boolean issucess = test.sc.nextBoolean();
		if (! issucess) {
			System.out.println("---------------很遗憾，没有被华为公司录用--------------------------");
			return issucess;
		}else {
			System.out.println("---------------恭喜你被华为公司录用了！--------------------------");
			return true;
		}
	}
}
