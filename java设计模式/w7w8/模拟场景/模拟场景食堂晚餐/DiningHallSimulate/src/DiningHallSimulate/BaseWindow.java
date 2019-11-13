package DiningHallSimulate;

public class BaseWindow extends Window {

	@Override
	public void process() {
		// TODO 自动生成的方法存根
		do{
			Student currentStudent = this.queue.currentStudent();
			if (currentStudent==null) {
				return;
			}
			String foodName = currentStudent.takeOrder();      //设置hash表和 student里的 wishFood就是为了这里
			Food f = this.foodList.get(foodName);
			if(f==null) {
				System.out.println("没有学生想要吃的菜");
			}else {
				f.accept(currentStudent);             //访问者模式
				f.accept(this.server);
			}
			System.out.println("请下一位学生取餐");
		}while(this.queue.next());
	}

}
