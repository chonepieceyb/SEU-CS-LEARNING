package Bridge_pattern_1;

public abstract class VedioPlayer {
	VedioFile vedioFile;

	public void setVedioFile(VedioFile vedioFile) {
		this.vedioFile = vedioFile;
	}

	public abstract void play(String fileName);
}
