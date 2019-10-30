package Command_Pattern;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		//客户端代码调用
		//新建学生
		Student me = new Student();
		SchoolDiningHall dininghall = new SchoolDiningHall();
		SchoolOrder order = new SchoolOrder(dininghall);
		me.setOrder(order);
		me.makeOrder("红烧牛肉面");
	}

}

	