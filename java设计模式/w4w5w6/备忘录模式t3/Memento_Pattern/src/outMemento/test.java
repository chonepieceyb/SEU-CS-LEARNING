package outMemento;

import Memento.Player;
import Memento.GameMemento;

public class test {
   
	public static void main(String[] args) {
		// TODO 自动生成的方法存根
	    // client 调用实例
		Player p = new Player();
		GameSystem gs = new GameSystem();
		//游玩
		p.play("现在玩家来到了大峡谷地区");
		p.printGameState();
	    //保存游戏
		gs.setGameMemento(p.saveGame());
		
		//游玩
		p.play("玩家来到了天空之柱地区，准备挑战boss");
		p.printGameState();
		//保存游戏
		gs.setGameMemento(p.saveGame());
		
		//玩家死亡
		System.out.println("玩家死亡了，回到之前储存点");
		
		//回档
		p.restartGame(gs.getGameMemento());
		p.printGameState();
		
	}

}


