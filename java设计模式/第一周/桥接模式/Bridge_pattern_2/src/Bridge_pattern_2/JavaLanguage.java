package Bridge_pattern_2;

public class JavaLanguage implements CodeLanguage {

	@Override
	public void useLanguage(String fileName) {
		// TODO 自动生成的方法存根
		System.out.println("日志"+fileName+"使用Java语言");
	}

}
