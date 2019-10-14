package Composite_Pattern_2;
public class test {

	public static void main(String[] args) {
		// TODO 自动生成的方法存根
		// 生成文件夹
		FolderScan folderscan = new FolderScan();
		// 添加图片和视频和文本
		int i=0;
		for (i =0;i<3;i++) {
			folderscan .add(new TextFileScan("文本"+i+".txt"));
		}
		for (i =0;i<2;i++) {
			folderscan .add(new ImageFileScan("图片"+i+".txt"));
		}
		for (i =0;i<4;i++) {
			folderscan .add(new VedioFileScan("视频"+i+".txt"));
		}
		//添加子文件夹 
		FolderScan folderscanSub = new FolderScan();
		for (i =0;i<5;i++) {
			folderscanSub.add(new TextFileScan("文本"+i+".txt"));
		}
		for (i =0;i<1;i++) {
			folderscanSub.add(new ImageFileScan("图片"+i+".txt"));
		}
		for (i =0;i<6;i++) {
			folderscanSub.add(new VedioFileScan("视频"+i+".txt"));
		}
		folderscan.add(folderscanSub);
		AntiVirus antiVirusSoftWare = new AntiVirus(folderscan);
		antiVirusSoftWare.scanVirus();
	}

}
