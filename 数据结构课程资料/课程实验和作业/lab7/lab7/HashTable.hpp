#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<iostream>
#include<iomanip>
using namespace std;
const int defaultSize = 100;
template<class E,class K>
struct  ChainNode
{
	K key;
	E data;
	ChainNode* link;
};

template<class E,class K>
class HashTable
{
public:
	HashTable(int d, int sz = defaultSize);
	~HashTable();
	bool search(const K k,  E& e);
	bool insert(const K k,const E& e);
	bool remove(const K k,  E&e);
	void output(void); //输出hash, hash的内容，装载因子等
	void staticticAnalyse(); //对hash表进行分析
	void reMake(int d, int sz); //重新构造hash
private:
	int divisor;   //除数取余法的除数，应该是一个质数
	int tableSize;  //散列表的大小桶的数目
	int nums;
	ChainNode<E,K>**ht;
	ChainNode<E,K>* findPos(const K k);
	bool deleteBucket(int i);  //删除第i 号桶的全部数据;
	void outBucket(int i);  //输出第i号桶的数据
	int bucketLength(int i); //计算桶的深度  桶的深度和ASL有关
	void deleteTable(); //删除整个表;
};

template<class E, class K>
HashTable<E,K>::HashTable(int d, int sz ):divisor(d),tableSize(sz),nums(0)
{
	if (tableSize < divisor)
	{
		cout << "输入的除数和hash大小不匹配，创建失败"<<endl;
		exit(1);
	}

	//分配空间
	ht = new ChainNode<E, K>* [tableSize];
	if (ht == nullptr)
	{
		cout << "空间未分配成功" << endl;
		exit(1);
	}
	//初始化
	for (int i = 0; i < tableSize; i++)
	{
		ht[i] = nullptr;
	}
}

template<class E, class K>
HashTable<E, K>::~HashTable()
{
	
	deleteTable();
	
}

template<class E, class K>
bool HashTable<E, K>::search(const K k,  E& e)
{
	ChainNode<E, K>* current = findPos(k);
	//如果没找到
	if (current == nullptr)
		return false;
	else
	{
		e = current->data;
		return true;
	}
}

template<class E, class K>
bool HashTable<E, K>::insert(const K k,const E& e)
{
	ChainNode<E, K>* current = findPos(k);
	if (current != nullptr)   //如果本来就存在了
		return false;
	else //如果原本的表里没有
	{
		int pos = static_cast<int>(k) % divisor;  //获取桶号
		//从顶端插入

		//创建新节点
		current = new ChainNode<E, K>;
		current->key = k;
		current->data = e;
		//链上去
		current->link = ht[pos];
		ht[pos] = current;
		nums++;  //数目+1

		return true;
	}
}

template<class E, class K>
bool HashTable<E, K>::remove(const K k,  E&e)
{
	int pos = static_cast<int>(k) % divisor;  //获取桶号
	ChainNode<E, K>* current = ht[pos];
    //如果第一个就是了
	if (current->key == k)
	{
		ht[pos] = current->link;
		e = current->data;
		delete current;
		nums--;
		return true;
	}
	else //如果第一个不是
	{
		ChainNode<E, K>* temp = current->link;   //temp 是要被删除的指针
		while (temp != nullptr)
		{
			//如果找到了
			if (temp->key == k)
			{
				current->link = temp->link;  //链上去
				//删除
				e = temp->data;
				nums--;
				delete temp;
				return true;
			}
			else
			{
				current = current->link;
				temp = temp->link;
			}
		}
	}
	return false;
}

template<class E, class K>
void  HashTable<E, K>::output(void) //输出hash, hash的内容，装载因子等
{
	cout << "--当前hash表的数据--" << endl;
	cout << " " << "除数取余法的除数为: " << divisor << "\t桶的个数: " << tableSize << "\t关键码的个数: "
		<< nums << endl;
	cout << " " << "桶号" << "\t\t关键码" << endl;
	for (int i = 0; i < tableSize; i++)
	{
		outBucket(i);
		cout << endl;
	}
}

template<class E, class K>
void  HashTable<E, K>::staticticAnalyse() //对hash表进行分析
{
	cout << "通过搜索算法测试比较次数，计算平均搜索长度ASL" << endl;
	//ASL与每个桶的深度有关
	//计算搜索成功的搜索长度
	int Sl = 0, Ul = 0;
	double Sa = 0, Ua = 0;
	for (int i = 0; i < divisor; i++)  //剩下的桶永远不会被用到所以不计入计算
	{
		int length = bucketLength(i);
		Ul += (length+1);
		if (length >0)  //只有桶中有元素才计算搜索成功的
		{
			Sl += ((length*(length + 1)) / 2);
		}
	}
	Sa = double(Sl) / double(nums);
	Ua = double(Ul) / double(divisor);
	cout << "\t\tSa = " << Sa << ",Ua = " << Ua << endl;

	//根据公式计算理论值
	cout << "\n利用alpha计算平均搜索长度ASL" << endl;
	double a ;
	a = double(nums) / double(divisor);
	cout << "n = " << nums << ", m = " << divisor << ", alpha = " << a << ", Sa = " << 1 + a / 2
		<< ", Ua = " << a;
			
}

template<class E, class K>
void HashTable<E, K>::reMake(int d, int sz)
{
	//先把原来整个表删掉,这里不能用初始化参数列表，因为初始化参数列表会先执行
	deleteTable();
	nums = 0;
	divisor = d;
	tableSize = sz;
	if (tableSize < divisor)
	{
		cout << "输入的除数和hash大小不匹配，创建失败" << endl;
		exit(1);
	}

	//分配空间
	ht = new ChainNode<E, K>*[tableSize];
	if (ht == nullptr)
	{
		cout << "空间未分配成功" << endl;
		exit(1);
	}
	//初始化
	for (int i = 0; i < tableSize; i++)
	{
		ht[i] = nullptr;
	}
}
template<class E, class K>
ChainNode<E,K>* HashTable<E, K>::findPos(const K k)   
{
	int pos = static_cast<int>(k) % divisor;  //获取桶号
	ChainNode<E, K>* tempPtr = ht[pos];
	while (tempPtr != nullptr)
	{
		//如果找到了
		if (tempPtr->key == k)
			break;
		else
		{
			tempPtr = tempPtr->link;
		}
	}
	return tempPtr;
	
}

template<class E, class K>
bool HashTable<E, K>::deleteBucket(int i)  //删除第i 号桶的全部数据
{
	if (i < 0 || i >= tableSize)
	{
		cout << "输入的i 非法" << endl;
		return false;
	}
	ChainNode<E, K>* current = ht[i];
	ChainNode<E, K>* dir = current;
    //先删除第一个
	if (current != nullptr)
	{
		current = current->link;
		nums--;
		delete dir;
		ht[i] = nullptr;
	}
	//删除之后的
	while (current != nullptr)
	{
		dir = current; 
		current = current->link;
		nums--;
		delete dir;
	}
	return true;
}

template<class E, class K>
void HashTable<E, K>::outBucket(int i) //输出第i号桶的data
{
	if (i < 0 || i >= tableSize)
	{
		cout << "输入的i 非法" << endl;
		return;
	}
	cout << i << "\t\t";
	ChainNode<E, K>* current = ht[i];
	while (current != nullptr)
	{
		cout << current->data << " ";
		current = current->link;
	}
	return;
}

template<class E, class K>
int HashTable<E, K>::bucketLength(int i)
{
	if (i < 0 || i >= tableSize)
	{
		cout << "输入的i 非法" << endl;
		return 0;
	}
	int length=0;
	ChainNode<E, K>* current = ht[i];
	while (current != nullptr)
	{
		length++;
		current = current->link;
	}
	return length;
}

template<class E, class K>
void HashTable<E, K>::deleteTable()
{
	if (ht != nullptr)
	{
		for (int i = 0; i < tableSize; i++)
			deleteBucket(i);
		delete[]ht;
		ht = nullptr;
	}
}
#endif


