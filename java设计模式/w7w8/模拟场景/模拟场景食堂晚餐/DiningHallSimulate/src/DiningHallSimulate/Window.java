package DiningHallSimulate;

import java.util.HashMap;

import DiningHallSimulate.StudentQueue.QueueIterator;

public abstract class Window {
	protected Visitor server;
	public void setServer(Visitor server) {
		this.server = server;
	}
	private StudentQueue sq = new StudentQueue();
	protected QueueIterator queue = this.sq.createQueueIterator();
	public void setQueue(QueueIterator queue) {
		this.queue = queue;
	}
	protected HashMap<String,Food> foodList = new HashMap<String,Food>() ;   //采用哈希表将Food对象和 Food名称（字符串）相匹配，为了符合模拟场景，这个用在process函数和student类的takeorder函数中
	public void addFood(Food f) {
		this.foodList.put(f.getName(), f);
	}
	public void addStudent(Student s) {
		this.queue.addStudent(s);
	}
	public int getNum() {
		return this.queue.getNum();
	}
	abstract public void process();      //按顺序排队点餐函数，由子类实现
}
