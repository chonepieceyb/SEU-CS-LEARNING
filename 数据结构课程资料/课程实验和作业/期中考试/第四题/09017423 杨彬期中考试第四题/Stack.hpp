#ifndef STACK_H
#define	STACK_H
template<class T>
struct StackNode
{
	//数据域
	T data;
	//指针域
	StackNode* next;
	//构造函数
	StackNode(T d, StackNode* n=nullptr) :data(d), next(n)
	{};
};
template<class T>
class Stack
{
public:
	Stack();
	~Stack();
	bool push(const T data); //压栈
	bool pop(T& data); //出栈操作并且取出最后的一个节点存在T中
	bool isEmpty()const;  //判空操作
	bool getTop(T& data)const;   //获取栈顶的元素,储存在data中
private:
	StackNode<T>* top; //栈顶的指针

};
template<class T>
Stack<T>::Stack()
{
	//top设置为空
	top = NULL;
}
template<class T>
Stack<T>::~Stack()
{
	StackNode<T>* current = top;
	StackNode<T>* dam;
	while (current != NULL)
	{
		dam = current;
		current = current->next;
		delete dam;
	}
}
template<class T>
bool Stack<T>::push(const T data) //压栈
{
	//分情况如果top为NULL
	if (top == NULL)
	{
		top = new StackNode<T>(data, NULL);
		if (top != NULL)
			return true;
		else return false;

	}
	else
	{
		//在头节点之前添加节点
		//建立一个新的节点
		StackNode<T>* newNode = new StackNode<T>(data, NULL);
		//把链挂上去
		if (newNode != NULL)
		{
			newNode->next = top;
			//跟新top
			top = newNode;
			return true;
		}
		else
			return false;
	}
}
template<class T>
bool Stack<T>::pop(T& data) //出栈操作并且取出栈顶的一个节点存在T中
{
	if (isEmpty()) //如果栈为空
		return false;
	else
	{
		//取出元素
		data = top->data;
		//删除
		StackNode<T>* dam = top;
		top = top->next;
		delete dam;
		return true;
	}
}
template<class T>
bool Stack<T>::isEmpty()const   //判空操作
{
	return top == NULL ? true : false;
}
template<class T>
bool Stack<T>::getTop(T& data)const   //获取栈顶的元素,储存在data中
{
	if (isEmpty())
		return false;
	else
	{
		T = top->data;
		return true;
	}
}
#endif // !STACK_H