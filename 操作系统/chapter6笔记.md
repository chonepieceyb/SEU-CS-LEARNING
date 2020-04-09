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
