package Bridge_pattern_2;

public class LoggerLiunx extends Logger {

	public LoggerLiunx(OutputFileForm o, CodeLanguage l) {
		super(o, l);
		// TODO 自动生成的构造函数存根
	}

	@Override
	public void outputLog(String fileName) {
		// TODO 自动生成的方法存根
		this.language.useLanguage(fileName);
		this.outputForm.outputForm(fileName);
		System.out.println("在Window平台上生成了日志"+fileName);
	}

}

