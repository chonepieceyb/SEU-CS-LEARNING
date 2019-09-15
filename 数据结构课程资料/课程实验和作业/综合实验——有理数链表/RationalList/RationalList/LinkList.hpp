#ifndef LINKLIST_H
#define LINKLIST_H
template<class T>
struct linkNode
{
	T data;
	linkNode* link;
	linkNode(T d=0, linkNode* l = nullptr) :data(d), link(l)
	{

	}

};

template<class T>
class LinkList
{
public:
	LinkList(T data=0);    //将附加头节点的初始data设为0
	virtual ~LinkList();
	bool insert(const int i, const T data);  //在第i个节点之后插入节点
	linkNode<T>* search(const T data)const;   //寻找数据为 data的节点 
	bool remove(const int i, T& t); //删除第i个节点
	bool isEmpty(); //判空
	void makeEmpty();//置空
	
	linkNode<T>* getHead()
	{
		return head;
	}
	linkNode<T>* getRear();

	int getLength()
	{
		return length;
	}
protected:
	//附加头节点,和尾部的节点
	linkNode<T>* head;
	linkNode<T>* findPos(const int i); //寻找第i个节点的位置
	int length;
};


template<class T>
LinkList<T>::LinkList(T data):length(0)
{
	head = new linkNode<T>(data,nullptr);  //初始化
}

template<class T>
LinkList<T>::~LinkList()
{
	makeEmpty();
	delete head;
}

template<class T>
bool LinkList<T>::insert(const int i, const T data)  //在第i个节点之后插入节点
{
	if (i == 0)  //特殊情况在头节点之后插入
	{
		if (head == nullptr)
			return false;
		linkNode<T>* newNode=new linkNode<T>(data, head->link);
		head->link = newNode;
		length++;
		return true;
	}
	else
	{
		linkNode<T>* current = findPos(i);
		if (current == nullptr )  //如果找不到第i个节点
			return false;
		//如果找到了
		linkNode<T>* newNode= new linkNode<T>(data, current->link);  //这里已经自动挂上去了

		current->link = newNode;
		length++;
		return true;
	}

}

template<class T>
linkNode<T>* LinkList<T>::search(const T data)const   //寻找数据为 data的节点
{
	if (isEmpty())
		return nullptr;
	linkNode<T>* current = head->link;
	while (current != nullptr )
	{
		if (current->data == data)
			return current;
		else
		{
			current = current->link;  //往下一个
		}
	}
}

template<class T>
bool LinkList<T>::remove(const int i, T& t) //删除第i个节点
{
	if (i == 1)   //特殊情况
	{
		if (head == nullptr)
			return false;
		else
		{
			if (head->link == nullptr)
				return false;
			else
			{
				linkNode<T>* dir = head->link;
				head->link = dir->link;
				delete dir;
				length--;
				return true;
			}
		}
	}
	else
	{
		linkNode<T>* current = findPos(i - 1);  //先找到第i-1个节点
		if (current == nullptr)  //如果找不到第i-1个节点,current为空
			return false;
		linkNode<T>* dir = current->link;
		if (dir == nullptr)  //如果被删除节点为空,或者被删除节点为头指针
			return false;
		else
		{
			current->link = dir->link;
			length--;
			delete dir;
			return true;
		}
	}
}

template<class T>
linkNode<T>* LinkList<T>::getRear()  //尾指针是最后一个有效节点的指针（包括头节点）
{                      
	if (head == nullptr)
		return nullptr;
	if (head->link == nullptr)
		return head;
	else
	{
		int i = length;
		return findPos(length);
	}
}

template<class T>
bool LinkList<T>::isEmpty() //判空
{
	if (head == nullptr)    //这个判断为了以访万一
		return true;
	else if (head->link == nullptr)   
		return true;
	else
		return false;
}

template<class T>
void LinkList<T>::makeEmpty()//置空
{
	if (isEmpty())  
		return;
	linkNode<T>* current = head->link;
	int l = 0;   //已经删除的长度
	while (current != nullptr  && l<length)
	{
		linkNode<T>* dir = current;
		current = current->link;
		l++;
		delete dir;
	}
	head->link = nullptr;
	length = 0;
}

template<class T>
linkNode<T>* LinkList<T>::findPos(const int i) //寻找第i个节点的位置
{
	if (i <= 0)    //判断边界
		return nullptr;
	if (isEmpty())  //如果链表为空返回空指针
		return nullptr;
	if (i > length)
		return nullptr;
	linkNode<T>* current = head->link;
	int k = 1;      //头节点是0号节点
	while (current != nullptr && k < i)
	{
		current = current->link;
		k++;
	}
	return current;
	
}
#endif // !LINKLIST_H