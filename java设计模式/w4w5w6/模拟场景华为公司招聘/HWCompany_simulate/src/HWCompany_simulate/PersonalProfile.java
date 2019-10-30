package HWCompany_simulate;

public class PersonalProfile {
	private String name;
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getFile() {
		return file;
	}
	public void setFile(String file) {
		this.file = file;
	}
	public Interviewee getInterviewee() {
		return interviewee;
	}
	public void setInterviewee(Interviewee interviewee) {
		this.interviewee = interviewee;
	}
	private String file;
	private Interviewee interviewee;
	public PersonalProfile(String name ,String file , Interviewee interviewee) {
		this.name = name;
		this.file = file;
		this.interviewee = interviewee;
	}
	public void printfile() {
		System.out.println(this.name+"的简历如下:");
		System.out.println(this.file);
	}
}
