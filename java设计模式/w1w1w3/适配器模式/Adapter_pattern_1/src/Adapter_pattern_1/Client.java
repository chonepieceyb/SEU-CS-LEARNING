package Adapter_pattern_1;

public class Client {
	Robot robot;
	public void setRobot(Robot robot) {
		this.robot = robot;
	}
	public void active() {
		this.robot.cry();
		this.robot.run();
		
	}
}
