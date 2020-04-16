# STL 内核

## deque

* deque是分段连续容器，它给使用者一种连续的感觉，但事实上只是**分段连续**的,一个buffer的数据是连续的，不同buffer的指针放在一个vector里。通过vector把buffer串接起来

* 对于push_back操作，如果尾部的 buffer没有满，那么直接放到尾部的buffer就可以了，如果尾部的buffer满了，那么重新申请一块buffer，将新的buffer作为新的尾部buffer，再把数据放进去(push_front同理)，所以deque可以实现双向扩充

* 其迭代器有四个变量，first 和 last (前闭后开)分别表示buffer的头尾，标识出了buffer的边界。node 标识了该buffer在 vector中的位置。cur指向buffer中的当前元素。

* deque的begin()返回start迭代器，end()返回finish迭代器

* 对于deque来说，中间的buffer(除了首尾的buffer) buffer都是**满的**

deque结构图:

![figure](./resources/16.jpg)

### deque 总体架构

GC2.9

```C++
template<class T, class Alloc =alloc , size_t BufSiz =0>
// buffer size 指的是每个buffer容纳的元素个数

class deque{
    public:
        typedef T value_type;
        typedef __deque_iterator<T,T&,T*,BufSiz> iterator; //迭代器对象
    protected:
        typedef pointer* map_pointer; // T**
    protected:
        iterator start;
        iterator finish;
        map_pointer map;  
        // map 就是把所有的buffer，都串起来的数组，
        //当map空间不够的时候会成长(和vector类似)
        size_type map_size;
    public:
        iterator begin() {return start;}
        iterator end() { return finish;}
        size_type size() const {return finish-start;}
}

//下面的操作依赖于迭代器的设计
reference operator[](size_type n)
{
    return start[differnce_type(n)];
}

reference front()
{return *start;}

reference back()
{
    iterator tmp = finish;
    --tmp;
    return *tmp;
}

size_type size() const
{
    return finish -start;
}

bool empty(0 const {
    return finish == start;
})
; 

// 和 BuffSiz 有关的函数， BuffSiz = 0 表示使用默认值

inline size_t __deque_buf_size(size_t n,size_t sz)
{
    return n !=0  ?  n : ( sz<512 ? size_t(512/sz):size_t(1))
    /*
     n 表示 buffer_size , sz表示一个元素的大小
     如果n不为0 表示 buffer_size由使用者指定。
     如果n为0采用默认值：
     如果元素大小 sz<512 返回 512/sz
     如果元素大小 sz>512 返回 1 
     这里的 512是字节
    */
}


```

### deque insert操作

```c++
// 在 position 处安插一个元素，其值为 x
iterator insert(iterator position, const value_type& x){
    if(position.cur == start.cur){
        //如果安插的点是deque的最前端
        //交给 push_front来做
        push_front(x);
        return start;
    }
    else if(position.cur == finish.cur)
    {
        //如果安插点是deque的最尾端
        //交给push_back来做
        push_back(x);
        iterator tmp = finish;
        --tmp;
        return tmp; // finish是最后一个元素的下一个
    }else{
        return insert_aux(position,x);
    }
}

template<class T, class Alloc, size_t BufSize>
//返回一个迭代器
typename deque<T,Alloc, BufSize>:: iterator
deque<T,Alloc,BufSize>::insert_aux(iterator pos , const value_type& x){
    difference_type index = pos-start; //获取position之前的元素个数
    value_type x_copy =x;
    if(index < size() /2){
        //如果安插点之前的元素个数较少
        //将节点往前推
        push_front(front());
        ...
        copy_forward(front2,pos1,front1) //把元素往前搬
    }
    else{
        //如果position之后的元素个数较少
        //就将节点往后搬
        push_back(back());
        ...
        copy_backward(pos,back2,back1);//将元素往后搬动
    }
    *pos = x_copy;// 设定新值
    return pos;
}
```

**deque**聪明的地方在于，由于deque的buffer机制，元素既可以往前搬也可以往后搬，在insert一个元素的时候，如果它离头比较近就往前搬，反之往后搬动，从而**最小化**搬动元素的次数

### deque迭代器

```c++
// 迭代器
template <class T, class Ref , class Ptr,size_t BuffSiz >
struct __deque_iterator{
    typedef random_access_iterator_tag iterator_catagory //(1) 支持随机访问 
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef size_t size_type;
    typedef ptrdiff_t  difference_type;
    typedef T** map_pointer ;
    typedef __deque_iterator self;

    T* cur;
    T* first;
    T* last;
    map_pointer node;
    ...
}

reference operator*() const
{return *cur; //返回data的引用}

pointer operator->()const
{return &(operator*());}

//计算 iterators之间的距离

/*
两个 iterators之间的距离: itr - x;
(1)两个iterators之间的 buffer(不包含两个迭代器本身所在的buffer)
也就是代码中的 (buffer_size()) * (node-x.node-1) 
注意 node-x.node-1是指针减法
(2) itr所在的buffer内，itr至该buffer开头的长度
也就是末尾的那一小段buffer的长度
代码中表现为: cur-first
(3) x所在的buffer内，x至该buffer末尾的长度
也就是开头的那一小段buffer的长度
代码中表现为: x.last-x.cur
*/
difference_type
operator-(const self& x)const
{
    return difference_type(buffer_size()) * (node-x.node-1) + (cur-first)+(x.last-x.cur);
}

// 通过下面的这些函数让使用者感受不到
//deque的分段，给使用者deque是连续的错觉

self& oeprator++(){
    ++cur;    //移到下一个元素
    if(cur==last){ //如果到达缓冲区尾端
        set_node(node+1); 
        //跳到下一个缓冲区的起点
        cur = first; 
    }
    return *this;
}
self oeprator++(int){
    self tmp = *this;
    ++*this;   // 利用 前++ 
    return tmp; //返回 迭代器对象
}

self& oeprator--(){
    // -- 和 ++ 不同 --要一开始就判断,
    // 产生区别的原因是 前闭后开区间
    if(cur == first){
        // 如果目前在缓冲区开头
        // 就跳到前一个缓冲区的最末端
        set_node(node-1); //
        cur = last;
    }
    --cur;
    return *this;
}

self oeprator--(int){
    self tmp = *this;
    --*this;   // 利用 前++ 
    return tmp; //返回 迭代器对象
}

void set_node(map_pointer new_node ){
    node = new_node ;
    first = *new_node; // new_node的内容本事就是 buffer的首地址
    last = first + difference_type(buffer_size());
}

self& oeprator+=(difference_type n){
    difference_type offset = n +(cur-first);
    if(offset >=0 && offset< difference_type(buffer_size())){
        // 如果目标位置在同一 buffer内
        cur +=n;
    }else{
        // 目标不再统一缓冲区内
        difference_type node_offset =
        offset >0 ? offset/difference_type(buffer_size()) 
        : -difference_type((-offset-1) / buffer_size() ) -1;

        // 切换到正确的缓冲区
        set_node(node + node_offset);
        // 切换到正确的元素
        cur = first+(offset - node_offset* difference_type(buffer_size()));
        return *this;
    }
}

self operator+(difference_type n) const{
    self tmp = *this;
    return tmp+= n;
}

self& operator-=(difference_type n ){
    return *this += -n;
}

self operator-(difference_type n)const
{
    self tmp = *this;
    return tmp-= n;
}
reference operator[](difference_type n)const
{
    return *(*this+n);
}

```

### queue 和 stack

* 事实上 stack 和 queue 是一种 adapter。 默认情况下，stack和 queue选择 deque作为其底层容器。queue/stack 也可以使用 list 作为底层容器。
* stack 和 queue 不允许遍历，也不提供 iterator。
* stack 可以选择 vector作为底层结构, 而 queue不能选择 vector 作为底层结构。
* stack 和 queue 都不能选择 set 或者 map 作为底层容器
