# C++11新特性

* **noexcept** ,`void foo() noexcept`这个关键字可以保证不丢异常。同时在**noexcept**内可以放置**bool**表达式，表明在什么时候保证不抛出异常，eg:`void foo() noexcept(true);`
* **override** ,这个关键字可以确保在子类的函数中，该函数一定是重写父类的函数。(如果不小心写错了，编译器会报错)
* **final** 关键字，1 写类的时候如果加上了**final**关键字，那么这个类不能被继承，2 如果用**final**修饰虚函数，那么该虚函数不能被**override** 
* **decltype** 通过使用**decltype** 这个关键字，可以让编译器找到一个表达式的type。这个关键字事实上类似于**typeof**这类函数的作用，只是现在**decltype**已经被写入标准里了

    >By using the new decltype keyword,you can let the compiler find out the type of an expression. This is the realizaton of the other requested typeof feature. However, the existing typeof implementations were inconsistent and incomplete, so c++11 intorduced a new key word.
    >
* **Lambdas** 允许定义**inline的函数，可以被作为参数或者局部对象来使用，**Lambdas** 改变了C++标准库的使用方法。

## noexcept

`void foo() noexcept(true);`

在上面的代码中，**noexcept**表明了`foo`不会抛出异常，但是如果`foo()`抛出异常了，那么程序就会终止，调用`std:terminate()`，`terminate()`这个函数在默认情况下又会调用`std::abort()`(这个函数会结束程序)

ps: **noexcept**可以用在**移动构造函数**上，(待深入研究，先插个桩)

>You need to  inform C++(specially std::vector) that **your move constructor and destructor does not throw** Then the move constructor will be called when the vector **grows**. **If the constructor is not noexept, std::vector can't use it** since then it can't ensure the exception guarantees demanded by the standard.
(注意 growable containers （会发生 memory reallocation)只有两种，vector和 deque)

## override 

```c++
struct Base{
    virtual void vfunc(float){};
};
struct Derrived1:Base{
    virtual void vfunc(int){
        /*
        这个函数，按照原意我打算重写父类的虚函数，
        但是我不小心参数写错了，这时候编译器会认为这个函数是一个新的函数
        而没有实现重写，换言之不会报错
        */
    }
}
struct Derived2:Base{
    virtual void vfunc(int ) override{}
    /*
    这里加上了override关键字
    告诉编译器这一定是重写父类的虚函数，
    但是这里参数列表写错了
    编译器会报错
    */
}
```

## decltype

eg:
```cpp
map<string,float> coll;
// 新写法
decltype(coll)::value_type elem; // 获取容器中元素的类型，来声明一个新的元素
// 旧写法
map<string,float>::value_type elem;

/*新旧写法的差别在于，新写法
可以用 decltype来获得容器的类型
而旧写法必须明确知道容器类型
*/
```

**decltype** defines a type equivalent to **the type of an expression** realization of the often requested **typeof** feature

### 三大应用:

* to declare return types

    ```c++
    template  <typename T1,typename T2>
    auto add(T1 x, T2 y)->decltype(x+y); // 里哟个和lambdas表达式类似的语法声明返回类型
    ```

* use decltype **in metaprogramming**

    ps:关于typename 一篇很好的文章： http://feihu.me/blog/2014/the-origin-and-usage-of-typename/

    ```c++
    template<typename T>
    void test18_decltype(T obj)
    {
        // 有了 decltype可以这么用
        typedef typename decltype(obj)::iterator iType;
        /*
        这里必须要加 typename
        应为这里使用了泛型编程，
        typename告诉编译器 T::iterator是一个类型，
        详情参考上面给出的文章
        */
        }
    ```

* **pass the type of a lambda**
    当我们需要把**lambda**组为 **hash function**或者**ordring or sorting criterion**的时候，我们需要用`decltype`获取lambda的type传递给模板参数，如下
    ```c++
    auto cmp =[](const Person&p1, const Person& p2){
        return p1.lastname()<p2.lastname();
    }
    std::set<Person,decltype(cmp)> cool(cmp); 
    // 不但需要传递cmp对象
    //（一定还要传递cmp作为参数否则大概率会报错，因为lambda函数是一个匿名类
    //没有默认构造函数），
    //还需要在模板指定类型，
    //这时候就可以用decltype来获得类型了。

    ```

## Lambdas

>A lambda is a definition of functionality that can be defined inside statement and expressions. Thus, you can use as lambda as an **inline finction**，Theminimal lambda function has no parameters and simply does something
>
eg:

```c++
auto I = []{
    std::cout<<"hello lambda"<<std::endl;
};
I();
```

### Lambdas的语法

$[...](...)multable_{opt}\:throwSpec_{opt}\:->\:retType_{opt}\{...\}$

ps:带有opt下标表示可选（当然也可不选），如果都没有选可以不写小括号，否则必须写小括号

* $[...]$ **lambda introducer**
    可以用来捕获(在lambda函数提内使用)外部变量(**nonstatic outside object**),如果是**Static** (eg:`std::out`)可以直接使用
  * [=] 表示外部变量是通过**传值**的方式传给**lambda**
  * [&] 表示外部变量是通过**传引用**的方式传给**lambda**
  * 传值和传引用的区别只可意会不可言传 `^_^`

  `[=,&y]`表示外部的 y 采用引用方式捕获，其它的所有的外部object采用传值的方式捕获
  `[x]` 表示外部的 x 采用传值的方式捕获

  ```c++
  int id =0 ;
  auto f =[id]()mutable{
      std::cout << "id:" << id << std::endl;
      ++id; // OK, 这里只有带了 mutable才能修改 id
  }

  // 上述代码等价于 (不完全等价，辅助理解)
  class Functor{
      private:
        int id = 42; // copy of ouside id 
      public :
        void operator()(){
            // 重载 ()方法
            std::cout << "id:" << id << std::endl;
             ++id; 
        }
  };
  Functor f;
  // 所以 Lambda的 Type相当于一个
  // 匿名的函数对象(function object or functor)
  ```

* $(...)$  **the parantheses for the parameters** 
    这里面就是像写一般函数一样，放参数

* $multable$ 是否可以修改被捕获的对象,如果是采用**传引用** 捕获的话不用加上**multabe**也可以修改

* $throwSpec$ 异常说明，比如可以加上`noexcept`表明不抛出异常
* $retType$ 指定返回的类型，如果不指定由函数体内的`return`语句自动推导
* $\{...\}$, 函数体


ps: **c++20**给lambda添加了很多新特性，在**c++20** 中，lambda甚至可以使用模板参数.....待研究，先插个桩 : 
https://zh.cppreference.com/w/cpp/language/lambda

### Lambda 注意事项

* Lambda 类似与一个函数对象
* Lambda 没有默认构造函数(很多的错误来源，比如在使用很多STL(如set)的时候)
* Lambda 没有赋值操作符
* 在STL中中函数，**Function object** 是一个非常有力的方式来自定义STL算法的部分行为(如比较方式)，但是写**Function object**（详情参照**Lambda 语法**等价于的部分）需要我们写类，有了**Lambda**之后就方便了很多。
