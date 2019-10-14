package Adapter_parttern_2;

public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		QuickSort qs = new QuickSort();
		BinarySearch bs = new BinarySearch();
		AdapterDataOperation dataoperation = new AdapterDataOperation(qs, bs);
		Client c = new Client( dataoperation);
		int[] array = {3,4,5,1,2};
		int value =5;
		c.sort(array);
		c.search(array,value);
	}

}
