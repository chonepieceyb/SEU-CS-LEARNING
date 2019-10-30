package Adapter_parttern_2;

public class Client {
	DataOperation dataOperation;
	public void setDataOperation(DataOperation dataOperation) {
		this.dataOperation = dataOperation;
	}
	Client(DataOperation dop){
		this.dataOperation = dop;
	}
	void sort(int[] array) {
		dataOperation.sort(array);
	}
    int search(int[] array, int value) {
		return dataOperation.search(array, value);
	}
}
