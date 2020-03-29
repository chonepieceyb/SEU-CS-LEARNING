#include<iostream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<getopt.h>
#include<errno.h>
#include<string.h>
#include<limits.h>

using namespace std;
void print_helpinfo(){
   //打印帮助信息
   cout<<"copy the content of src file to dst file, dst can be a new file or an existent file.\n";
   cout<<"SYNPSIS"<<endl;
   cout<<"\tfile_tool [option] src dst"<<endl;
   cout<<"OPTION\n";
   cout<<"-f --force if dst is an existent file, add this flag will overwrite the content of dst with src\n";
   cout<<"-a --append if dst is an existent file, add this flag will append the content of src the the tail of dst\n";
   cout<<"-h --help print help info\n";
   return;
}
void copy_file( char* src, char* dst , const short flag){
	//检查 src 是否为普通文件
	struct stat sb ;
	stat(src,&sb);
	if (!S_ISREG(sb.st_mode)){
		printf("bad src! %s\n",strerror(errno));
		return ;
	}
	int src_fd = open(src,O_RDONLY);
	int dst_fd = open(dst,O_CREAT|O_EXCL|O_RDWR,S_IRWXU);
	//尝试创建 dst
	if(dst_fd<0){
	    // 如果文件已经存在
	    if(flag ==-1){
	       printf("dst is alwrady exist , please give additional argument ! use file_tools -h for help!\n");
	       return ;
	    }
	    dst_fd = ( flag == 1) ? open(dst, O_RDWR|O_APPEND) : open(dst,O_RDWR|O_TRUNC);
	    if(dst_fd < 0){
	    	printf("some error happen! %s\n",strerror(errno));
		return ;
	    }
	}
	// 判断 src 和 dst 是不是同一个文件 防止 无限复制
	char abs_path_src[PATH_MAX] , abs_path_dst[PATH_MAX];
	realpath(src,abs_path_src);
	realpath(dst,abs_path_dst);
	if ( strcmp(abs_path_src, abs_path_dst) == 0){
		printf("the src and dst are the same!\n");
		return ;
	}
	// 开始进行文件操作, 一次读写 1k byte
	char buffer[1024]={0};  
	while(1){
	  int  count = read(src_fd, &buffer , 1024 ); // 使用 linux 系统调用读取 1024个字节
	  if(count ==0 ){
		printf("copy successful\n");
		return ;
	  }else if(count < 0){
	  	printf("some error happen! %s\n", strerror(errno));
		return ;
	  }else{
		// 向dst写字节
		int  wcount = write(dst_fd , &buffer , count);
	        if(wcount < 0){
			printf("some error happen! %s\n", strerror(errno));
			return;
		}
	  }
	}	
	return ;
}

extern int optind;     // 解析参数需要的变量

int main(int argc, char** argv){
  //解析命令行参数
  short  flag = -1;          // flag 根据解析参数的结果 -1初始值，0 force, 1 append
  while(1){
	 int option_index = 0;
	 int c; 
	 static struct option long_options[] = {
		 {"force",0,NULL,'f' },
		 {"append",0,NULL,'a'},
		 {"help",0,NULL,'h'},
	 };
	 c = getopt_long(argc,argv,"fah",long_options,&option_index);
	 if(c==-1){
		 // 参数解析完成
	 	break;
	 }
	 switch(c){
	 	case('?'):            //解析到未知参数
			return 1 ;
		case('a'):            
		       flag = 1; break;
	        case('f'):
		       flag = 0; break;
	        case('h'):
		       print_helpinfo();  return 0;
	  	default:
		       printf("some unknown error!\n");
		       return 1 ;
	 }
	 
  }
  //获得 src 和 dst
  if (argc - optind <2 ){
	// 判断参数的个数是否足够，最后两个参数需要是 src 和 dst  
  	cout<<"please enter the path of both src and dst\n";
  }
  char* src = argv[optind],*dst = argv[optind+1];
  copy_file(src, dst ,flag);

  return 0;
}

