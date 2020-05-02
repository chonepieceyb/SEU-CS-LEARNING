# Socket编程

每个函数调用都要检查是否返回错误，我们可以定义包裹函数来简化程序，由包裹函数调用实际的函数，检查返回值

```c++
sockfd = Socket(AF_INET,SOCK_STREAM,0);
int Socket(int family, int type,int protocol){
    int n;
    if((n=socket(family,type,protocol))<0) err_sys("socket error")
    return 0 
}

```

上述方法不推荐。

在 Linux系统中有一个 errno 全局变量，当发生错误的时候， errno 被置设置为相应的正值，返回-1;