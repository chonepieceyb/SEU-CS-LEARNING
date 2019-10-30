package outMemento;
// 在 备忘录包外定义 careTaker类 防止破坏封装性，memento类的内部成员只能被Originator类访问
import Memento.GameMemento;

public class GameSystem {
	private GameMemento gameMemento;

	public GameMemento getGameMemento() {
		return gameMemento;
	}

	public void setGameMemento(GameMemento gameMemento) {
		this.gameMemento = gameMemento;
	}



}
