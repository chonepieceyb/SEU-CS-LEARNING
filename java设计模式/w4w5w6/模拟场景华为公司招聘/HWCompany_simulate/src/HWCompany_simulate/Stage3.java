package HWCompany_simulate;

import java.util.Scanner;

public class Stage3 extends CampusRecruit {
	// 华为校招面试类
	@Override
	public boolean recruit(PersonalProfile file) {
		// TODO 自动生成的方法存根
		System.out.println("----------------进入华为面试阶段------------------------");
		file.printfile();
		System.out.println("请决定是否通过");
	    boolean issucess = test.sc.nextBoolean();
		if (! issucess) {
			System.out.println("---------------很遗憾，没有通过华为的面试--------------------------");
			return issucess;
		}else {
			System.out.println("---------------恭喜你通过了华为的面试,进入下一个阶段的考核--------------------------");
			return this.getNextRecruit().recruit(file);
		}	
	}
}
