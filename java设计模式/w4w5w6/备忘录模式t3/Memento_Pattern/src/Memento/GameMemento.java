package Memento;

public class GameMemento {
	
	private String gameState;
	//不加public 修饰符 默认包内可见
	String getGameState() {
		return gameState;
	}
    void setGameState(String gameState) {
		this.gameState = gameState;
	}
	GameMemento(String gs) {
		// TODO 自动生成的构造函数存根
		this.gameState = gs;
	}

}



