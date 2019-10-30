package Memento;

public class Player {
	private String gameState;
	public Player() {
		// TODO 自动生成的构造函数存根
		this.gameState="游戏初始";
	}
	public GameMemento saveGame() {
		return new GameMemento(this.gameState);
	}
	public void restartGame(GameMemento gm) {
		this.gameState = gm.getGameState();
	}
	
	
	public void play(String gameState) {
		//改变游戏状态的函数，play 比较符合场景
		this.gameState = gameState;
	}
	public void printGameState() {
		//方便查看状态的函数
		System.out.println(this.gameState);
	}
}
