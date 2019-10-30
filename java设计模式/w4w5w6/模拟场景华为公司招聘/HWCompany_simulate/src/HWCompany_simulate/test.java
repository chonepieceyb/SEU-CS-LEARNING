package HWCompany_simulate;

import java.util.Scanner;

public class test {
	static Scanner sc = new Scanner(System.in); 

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		// 客户端类
		//设置 面试者
		CommonInterviewee student = new CommonInterviewee();
		PersonalProfile studentFile = new PersonalProfile("王明", "本人毕业与东南大学计算机学院，绩点年级第一！", student);
		student.setFile(studentFile);
		
		CommonInterviewee nostudent = new CommonInterviewee();
		PersonalProfile nostudentFile = new PersonalProfile("张三", "我曾经在腾讯公司工作过", nostudent);
		nostudent.setFile(nostudentFile);
		
		SeniorTalents professor  = new SeniorTalents();
		PersonalProfile professorFile = new PersonalProfile("张教授", "在计算机一类会议中发表论文20余篇", professor);
		professor.setFile(professorFile);
		
		SeniorTalents professor2  = new SeniorTalents();
		PersonalProfile professorFile2 = new PersonalProfile("王教授", "在计算机一类会议中发表论文10余篇", professor2);
		professor2.setFile(professorFile2);
		
		//建立华为公司
		HWCompany HUAWEI = HWCompany.getInstance();
		
		//建立校园招聘制度
		Stage1 campusRecruit1 = new Stage1();     //HR 初试
		Stage2 campusRecruit2 = new Stage2();    //技术考核
		Stage3 campusRecruit3 = new Stage3();   // 面试
		Stage4 campusRecruit4 = new Stage4() ;  //终试
		//设置校园招聘的流程
		campusRecruit1.setNextRecruit(campusRecruit2);
		campusRecruit2.setNextRecruit(campusRecruit3);
		campusRecruit3.setNextRecruit(campusRecruit4);
		campusRecruit4.setNextRecruit(null);
		
		//设置社会招聘
		RealSocialRecruit realSocalRecruit = new RealSocialRecruit();   //真实社招
		ProxyCompany recruitCompany = new ProxyCompany("南京社会招聘有限公司"); //代理公司
		recruitCompany.setRealSocialRecruit(realSocalRecruit);
		
		//设置华为总部的直接招聘
		HWRecruit  hwRecruit = new HWRecruit();
		HUAWEI.setHwRecruit(hwRecruit);
		//设置适配器
		HWRecruitAdapter hwRecruitAdapter = new HWRecruitAdapter();
		hwRecruitAdapter.setHUAWEI(HUAWEI);
		 
		 //开始招聘流程
		 //校园招聘
		 System.out.println("校招结果："+ campusRecruit1.recruit(studentFile)+'\n');
		 //社招
		 System.out.println("社招结果："+ recruitCompany.recruit(nostudentFile)+'\n');
		//高等人才社招，直接被进入华为公司本部招人流程
		 System.out.println("高级人才社招结果："+ hwRecruitAdapter.recruit(professorFile)+'\n');
		//华为公司直接找人
		 System.out.println("华为公司直接招人结果："+ HUAWEI.hwRecruit(professor2)+'\n');
		 
		 //测试 普通人才走华为公司的高级人才通道
		 System.out.println("华为公司直接招人结果："+ hwRecruitAdapter.recruit(studentFile)+'\n');
		 sc.close();
	}

}
