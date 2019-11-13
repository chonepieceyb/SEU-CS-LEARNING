package DiningHallSimulate;

public class test {



	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		//测试类
		//菜品 有三种 黄焖鸡 掉渣饼和牛肉面
		HangMenJi food1 = new HangMenJi(13.0, "黄焖鸡");
		DiaoZhaBing food2 = new DiaoZhaBing(11.5, "掉渣饼");
		NiuRouMian food3 = new NiuRouMian(10.0,"牛肉面");
		//食堂
		//桃园食堂
		TAODiningHall taoyuan = new TAODiningHall();
		//假设有2个窗口
		BaseWindow w1 = new BaseWindow();
		BaseWindow tempW = new BaseWindow();
		BaseWindow w2 = new  BaseWindow();  //窗口2 比窗口1更加高级 装饰模式
		//一个窗口有一个厨师
		Server s1 = new Server();
		Server s2 = new Server();
		//设置窗口服务员和菜品
		w1.setServer(s1);
		w2.setServer(s2);
		w1.addFood(food1); //窗口1 卖黄焖鸡
		w2.addFood(food2); //窗口 2、3买掉渣饼和牛肉面
		w2.addFood(food3);
        //设置椅子
  		SeatList seats1 = new SeatList();
		SeatList seats2 = new SeatList();
		seats2.createSeatIterator().addSeat(new Seat()); //添加椅子
		//组装桃园食堂
		taoyuan.setSeats(seats1.createSeatIterator());
		//taoyuan.addWindow(w1);
		taoyuan.addWindow(w2);
		// 梅园食堂配置和桃园食堂基本相似只是增加了一些新的功能
		MEIDiningHall meiyuan = new MEIDiningHall(taoyuan);
		
		//学生
		//付款方式
		Cash cash = new Cash();
		Card card = new Card();
		Student student1 = new Student("小王");
		student1.setPayMethod(card);
		student1.wishFood="黄焖鸡";
		Student  student2 = new Student("小明");
		student2.setPayMethod(card);
		student2.wishFood="牛肉面";
		Student student3 = new Student("小刚");
		student3.setPayMethod(cash);
		student3.wishFood="掉渣饼";
		//学生去食堂吃饭了 
		taoyuan.lineup(0, student1);
		taoyuan.lineup(0, student2);
		taoyuan.lineup(0, student3);
		//开始点餐 一个个顺序进行，没有用多线程
		System.out.println("-----------------------桃园----------------------------");
		taoyuan.process();
		
 	}

}
