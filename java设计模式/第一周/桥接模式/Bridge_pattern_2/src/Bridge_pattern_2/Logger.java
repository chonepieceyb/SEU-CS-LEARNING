package Bridge_pattern_2;

public abstract class Logger {
	OutputFileForm outputForm;
	public void setOutputForm(OutputFileForm outputForm) {
		this.outputForm = outputForm;
	}
	public void setLanguage(CodeLanguage language) {
		this.language = language;
	}
	CodeLanguage language;
	
	public Logger(OutputFileForm o, CodeLanguage l) {
		this.outputForm = o;
		this.language =l;
	}
	public abstract void outputLog(String fileName);
	
}
