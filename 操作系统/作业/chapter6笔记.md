# Process synchronization

Objectives

* To intorduce the critical-section problem, whose solutions can be used to ensure the consistency of shared data
* To present both software and hardward solutions of the critical-section porblem.

## 背景

对共享数据的并发访问会导致数据的不一致性

* Race condition (竞争局面——读写交错)

  * The situation where several processes access and manipulate shared data concurrently.
  * The final  value of the shared data depends upon which process finished last
  
  修改丢失，比如生产者(producer) 再修改一个数据，但是还没有改完。这时候发生并发访问，消费者修改同一个数据修改完成之后，回到生产者进程，这时候生产者继续修改刚才的数据，导致消费者的修改都被生产者抹杀了。

* Solution:


## The Critical-Section Problem (临界区)

临界区:用来访问(access，包含读写)共享数据(共享变量)的代码段(code segment)

### The critical section problem
    
the problem is how to design a protocal that

* One process is excuting in **its critical section**, no other process is to **be allowed** to **execute** in its **critical section** of accessing **the same** shard data

  对相同的共享数据，在任何时刻只能允许一个进程执行该变量的临界区代码(access)。(不同的共享数据可以有另外一个进程执行相应的临界区代码)，比如同时只能有一个进程access count变量。在临界区内将并发执行转化为串行执行

* General structure of process Pi

  ```c++
    do{
        entry section
            critical section
        exit section
            
    }

  ```

### 临界期问题是否解决的指标

* **Mutual Exclusion(互斥)**

  不允许两个进程不同时进入临界区(同一数据的)

* **Progress (推进，空闲让进)**

  * if no process is excuting in ints critical section adn there exits some processes that whsh to oenter their critical section
  
  * The selection of the processes that will enter the cirtical section next connot be **postponed infinitedly**

  可能有很多进程同时要进入临界区，所以可能会有延迟，但是不能无限制地推迟.也就是不能有 临界区是空闲的但是没有进程能进去的情况

* **Bounded Waiting** 

  A bound must exixt on the number of times for the processes waiting for the

  不能无限地等待下去，无法进入临界区, 不能出现饥锇现象(有一个在临界区，其它所有的都在等)

算法2:

```c++
Process Pi
do{
  flag[i] = true;
  while(flag[j] == true);
      critical section
  flag[i] = false;
      critical section
  flag[i] = falase;
}
Process Pj
do{
  flag[j] = true;
  while(flag[i] ==true);
      critical section;
  flag[j] = false;
      remainder
  section
}while(true);

// 当同时举手，也就是当第一行代码交替进程的时候
// 会导致flag[i] 和 flag[j] 同时为true的时候，导致了死锁。
// 不能中断的动作是原子动作
```

算法3:

```c++
ProcessPi
do{
  flag[i] = true;
  turn = j;
  while(flag[j] = true && turn ==j);
      critical section
  flag[i] = false;
      remainder section
}while(true)

// turn 只有一个值可以避免 无限等待的问题 和 互斥访问的问题
// 至于空闲让进，如果临界区是空闲的，必有一个flag是 false, 又由于只有一个turn，所以空闲让进。

```

## 硬件方式的同步

1. 在访问临界区的时候关中断，这样就不会被打断了，虽然简单，但是存在问题.
    * 在访问临界区代码的时候，发生紧急事件。
    * 对于多CPU架构采用这种方式意味着要关闭所有CPU的中断(又涉及到多CPU之间的等待和通信)

2. 原子操作不能打断。

```c++
Process Pi
do{
  while(TestAndSet(lock));
    critical section
  lock = false;
    remainder section 
}
```

如果两个 `TestAndSet()` are executed simultaneously each on a different CPU, they will be ren sequeitially in som arbitrary order.

上述算法的问题是，争夺锁没有排队，可能导致饥锇现相

算法2:

Bounded-waiting with TestAndSet()

```c++
do{
  Waiting[i] = true;
  key = true;
  while(Waiting[i]==true && key == true) key = TestAndSet(lock);
  Waiting[i] = fakse; // key-fakse
    Waiting[i] = false;
       critical section
  j =(i+1)%n;
  while((j!=i)&& Waiting[j.] ==false ) j =(j+1)%n;
  if (j==i) lock = false ;
  else Waiting[j] = false; // 把waiting[j] = false , 但是不设置 lock为false,就意味着只有 j这个进程能够打破while循环
  remainder section
  
  /*
  因为只有 j的 waiting 被设为 false了，这时候不管 lock是否为false，j这个排在前面的进程都可以进来。而排在后面的进程，其waiting都是true，并且lock这时候是true，所以其它的进程都进步来
  这个waiting[j] 可以比喻为后门。
  
  临界区有正门(lock)和后门(waiting)，不管是正门还是后门都只能从里面开。
  进入临界区的进程根据现在有没有进程在排队来打开正门或者后门
  */
}while(true);

```

## 信号量

信号量可以看成一个对象，它有一个整数值，并且有两个原子操作。

```c++
wait(S){
  while(S<=0) waiting;
  S.value--;
}
```

* Binary semaphore 
  互斥锁，互斥型信号量

* Counting semaphore
  计数型信号量

用信号量解决多个生产者的问题

```c++
do{
  // produce an item
  wait(empty);
  wait(mutex);  //互斥锁
    Critical Section
  signal(mutex);
  signal(full);
}while(true)

```

```c++
do{
  wait(full);
  wait(mutex);
    Critical Section
  signal(mutex);
  signal(empty);

  // consume the item in nextc
}while(TRUE)



```

### Readers and Writers Problem (读者-写者问题)

脏数据: 前后数据不一致，写的进程修改了一半，读的进程就读数据了

* 同一时刻允许多个读进程读数据.
* 同一时刻只允许一个写进程写数据.
  
#### 用信号量解决读者写者问题

Shared Data

* Data set 
* Semaphore mutex initialized to 1
* Seaphore wrt initialized to 1
* Integer readcount initialized to 0

写者:

```c++
do{
  wait(wrt);  // 判断能不能写
    Critical Section
    // writing is performed
  signal(wrt);

}while(TRUE)

```

读者:

```c++
do {
  wait(mutex);  //对 readcount变量进行保护，互斥锁
    readcount++ // Critical Section
    if(readcount ==1) wait(wrt); 
    // 如果是第一个读者，需要判断写者
    // 有没有在写，同时读者在读的时候
    // 把 wrt 信号量 -1 是的写者在读
    //的时候不能写了
    signal(mutex) // 这里 signal 必须在 if 语句之后，因为前面的 if 语句对 readcount 进行了判断
        // reading is performed
    wait(mutex);
      readcount--; // Crital Section
      if(readcount ==0) signal(wrt);
      // 如果是最后一个读者，wrt=1，表明这时候没有读者了，写者可以开始写了
    signal(mutex); // 同上面那个 mutex
}while(TRUE);

```

上述代码对读者友好，对读者很不友好，可能导致写者饥锇

### 哲学家问题

### 信号量的问题



### 阅览室问题

### 水果篮问题

```c++



```