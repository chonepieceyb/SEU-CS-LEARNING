package DiningHallSimulate;

import java.util.ArrayList;

public class StudentQueue {
	private ArrayList<Student> students=new ArrayList<Student>();
	public QueueIterator createQueueIterator() {
		return new QueueIterator();
	}
	class QueueIterator{
		public boolean next() {
			if(!students.isEmpty()) {
				students.remove(0);
				return true;
			}else {
				System.out.println("没有学生排队了");
				return false;
			}
		}
		public Student currentStudent() {
			if(! students.isEmpty()) {
				return students.get(0);
			}else {
				System.out.println("没有学生排队了");
				return null;
			}
		}
		public void addStudent(Student s) {
			students.add(s);
		}
		public int getNum() {
			return students.size();
		}
	}
}
