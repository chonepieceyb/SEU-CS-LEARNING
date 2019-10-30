package Bridge_pattern_2;

public class LoggerWindows extends Logger {

	
	public LoggerWindows(OutputFileForm o, CodeLanguage l){
		super(o,l);
	}
	@Override
	public void outputLog(String fileName) {
		// TODO 自动生成的方法存根
		this.language.useLanguage(fileName);
		this.outputForm.outputForm(fileName);
		System.out.println("在Window平台上生成了日志"+fileName);
	}

}
