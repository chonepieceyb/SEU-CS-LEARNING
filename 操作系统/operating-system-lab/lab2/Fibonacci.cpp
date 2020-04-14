/* 
author chonepieceyb, operatiing-system lab2 

2020年 03月 31日 星期二 21:24:51 CST
*/
#include<iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string>
using namespace std;

int main( int argc, char** argv){
	if(argc!=2){
		cout<<"请输入一个参数\n";
		exit(-1);
	}
	int parm = std::stoi(string(argv[1]));   // 将字符串转化为 整形
	if(parm<0){
		cout<<"参数不能小于0！"<<endl;
		exit(-1);
	}
	// 开辟子进程
	int pid = fork();
	if(pid<0){
		cout<<"fail to fork child process!\n";
		exit(-1);
	}else if(pid ==0){
		//如果是子进程的话
		if(parm ==0){
			printf("fib%d = %d\n", 0 , 0);
		}else if(parm == 1){
			printf("fib%d = %d\n", 1 , 1);
		}else{
			long fb1 = 0 , fb2 = 1;
			printf("fib%d = %d\n", 0 , 0);
			printf("fib%d = %d\n", 1 , 1);
			for(int i =2 ; i<=parm;i++){
				long v = fb1 + fb2;
				printf("fib%d = %ld\n",i , v);
				fb1 = fb2;
				fb2 = v ;	
			}
		}
		exit(0);
	}else{
		int status;
		waitpid(pid,&status,WUNTRACED);          // waitpid的作用和wait 类似等待 pid = pid的子进程结束;
		exit(0);
	}
		
}

