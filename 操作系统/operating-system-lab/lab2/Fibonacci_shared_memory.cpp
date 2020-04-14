
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
#include <sys/ipc.h>
#include <sys/shm.h>
#define MAX_SEQUENCE 50           // fbi 最大的个数
using namespace std;

struct shared_data{
	long fib_sequence[MAX_SEQUENCE];     //数组
	int sequence_size;
};

int main( int argc, char** argv){
	if(argc!=2){
		cout<<"请输入一个参数\n";
		exit(-1);
	}
	int parm = std::stoi(string(argv[1]));   // 将字符串转化为 整形
	if(!(parm>=0&& parm <MAX_SEQUENCE) ){
		cout<<"参数不能小于0！或者大于等于50"<<endl;
		exit(-1);
	}
	// 创建共享内存	
	int shm_id = shmget((int)getpid(),sizeof(shared_data),IPC_CREAT);
	if(shm_id ==-1){
		//如果没有成功开辟共享内容
		cout<<"child p fail to get  a shared memory !"<<endl;
		exit(-1);
	}	
	// 开辟子进程
	int pid = fork();
	if(pid<0){
		cout<<"child p fail to fork child process!\n";
		exit(-1);
	}else if(pid ==0){
		//如果是子进程的话
		// attach到共享进程
		void* shm = shmat(shm_id,NULL,0);    // 由操作系统自动分配，有读写权限
		if(shm == (void*)-1){
			cout<<"child p fail to attach to shared memory!\n";
			exit(-1);
		}
                shared_data * share =	 (shared_data*)shm;      //强转
		if(parm ==0){
			share->fib_sequence[0] = 0;
			share->sequence_size = 1;
		}else if(parm == 1){		
			share->fib_sequence[1] = 1;
			share->sequence_size =2;
		}else{
			share->fib_sequence[0] = 0;
			share->fib_sequence[1] = 1;
			share->sequence_size =2;
			long fb1 = 0 , fb2 = 1;
			for(int i =2 ; i<=parm;i++){
				long v = fb1 + fb2;
				share->fib_sequence[i] = v;
				share->sequence_size ++ ;
				fb1 = fb2;
				fb2 = v ;	
			}
		}
		// detach 
		if(shmdt(shm)==-1){
			cout<<"child p fail to detach shared memory!\n";
			exit(-1);
		}else{
			exit(0);
		}
	}else{


		int status;
		waitpid(pid,&status,WUNTRACED);          // waitpid的作用和wait 类似等待 pid = pid的子进程结束;
		// attach to shared memory 
		void* shm = shmat(shm_id,NULL, SHM_RDONLY);    // 由操作系统自动分配，只有读权限
		if(shm == (void*)-1){
			cout<<"main process fail to attach to shared memory!\n";
			exit(-1);
		}
		shared_data* share = (shared_data*)shm;      //强转
		for(int i=0;i<share->sequence_size;i++){
			printf("fib%d=%ld\n",i,share->fib_sequence[i]);
		}
		// detach 
		if(shmdt(shm)==-1){
			cout<<"main  p fail to detach shared memory!\n";
			exit(-1);
		}else{
			exit(0);
		}
		// delete shared memory 
		shmctl(shm_id, IPC_RMID ,NULL);
		exit(0);
	}
		
}

