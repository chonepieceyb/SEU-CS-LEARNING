
#ifndef ARRAY_H
#define ARRAY_H
#include<iostream>
using namespace std;
template<int T_numberOfElements, typename T_elementType>
class Array
{
	template<int T_numberOfElements, typename T_elementType>friend  ostream& operator<< (ostream& output, const Array< T_numberOfElements, T_elementType>&); 
	template<int T_numberOfElements, typename T_elementType>friend  istream& operator>> (istream& output, const Array< T_numberOfElements, T_elementType>&);
	//在模板类中使用友元函数的时候在类中必须也要加上模板类的模板声明，参数是类的画相应加上
private:
	T_elementType* m_Tarray;
	int m_iSize;
public:
	Array();
	Array(const Array&);
	~Array();
	int size(void)const;
	void operator=(const Array&);
	T_elementType& operator[](int);

};
template<int T_numberOfElements, typename T_elementType>
Array<T_numberOfElements, T_elementType>::Array()
{
	m_iSize = T_numberOfElements;
	if (m_iSize <= 0)
		throw invalid_argument("The size of the array is invalid");
	m_Tarray = new T_elementType[m_iSize];

}
template<int T_numberOfElements, typename T_elementType>
Array<T_numberOfElements, T_elementType>::Array(const Array& t_right)
{
	if (m_iSize != t_right.m_iSize)
		throw invalid_argument("The asignment is invalid")
		for (int i = 0;i < m_iSize;i++)
			m_Tarray[i] = t_right.m_Tarray[i];
}
template<int T_numberOfElements, typename T_elementType>
Array<T_numberOfElements, T_elementType>::~Array()
{
	delete[] m_Tarray;
	m_Tarray = nullptr;
}
template<int T_numberOfElements, typename T_elementType>
int Array<T_numberOfElements, T_elementType>::size(void)const
{
	return m_iSize;
}
template<int T_numberOfElements, typename T_elementType>
void Array<T_numberOfElements, T_elementType>::operator=(const Array& t_right)
{
	if (m_iSize != t_right.m_iSize)
		throw invalid_argument("The asignment is invalid")
		for (int i = 0;i < m_iSize;i++)
			m_Tarray[i] = t_right.m_Tarray[i];
}
template<int T_numberOfElements, typename T_elementType>
T_elementType& Array<T_numberOfElements, T_elementType>::operator[](int x)
{
	return m_Tarray[x];
}

template<int T_numberOfElements, typename T_elementType>
 ostream& operator<< (ostream& output, const Array<T_numberOfElements,  T_elementType>& right)  ///这里也要加尖括号
{
	for (int i = 0;i < right.size();i++)
		output << right.m_Tarray[i] << " ";
	return output;
}
template<int T_numberOfElements, typename T_elementType>
  istream& operator>>(istream& input, const Array< T_numberOfElements, T_elementType>&right)
{
	for (int i = 0;i < right.size();i++)
		input >> right.m_Tarray[i];
	return input;
}
  //模板类函数的实现如果不是定义在头文件中，可能会出现链接器错误
#endif // !ARRAY_H
