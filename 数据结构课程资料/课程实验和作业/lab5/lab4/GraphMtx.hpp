#ifndef GRAPHMTX_H
#define GRAPHMTX_H
#include<iostream>
#include<fstream>
#include<iomanip>

#include"SeqQueue.hpp"
using namespace std;
const int defaultSize = 20;
template<class V, class W>
class GraphMtx
{
/*
template<class V,class W>
friend ifstream& operator>>(ifstream& fin, GraphMtx<V,W>& graph);
template<class V, class W>
friend ofstream& operator<<(ofstream& fout, GraphMtx<V,W>& graph);
*/
public:
	enum GraphType{ UNDIRECTED,DIRECTED };
	GraphMtx(W max, GraphType type = UNDIRECTED,int maxV = defaultSize);  //默认是无向图
	~GraphMtx();
	bool isGraphEmpty()
	{
		return numVertexes <= 0 ? true : false;
	}
	
	bool isGraphFull()
	{
		if ( numVertexes >= maxVertexes|| numEdges >= maxVertexes* (maxVertexes - 1))  //如果顶点满(这里判断只考虑有向简单图)
		{
			return true;
		}
		else
			return false;
	}
   
    int numOfVertexes()
	{ return numVertexes; }

	int numOfEdges()
	{
		return numEdges;
	}

	bool getVertexValue(int i, V& value) // 返回第i 个顶点的值储存在value中
	{
		if (i < 0 || i >= numVertexes)   //如果越界的话
		{
			return false;
		}
		else
		{
			value = vertexesList[i];
			return true;
		}
	};

	bool getEdgeWeight(int v1, int v2, W& weight)   //返回 顶点v1 和 v3 之间边的权值
	{
		if (v1 < 0 || v1 >= numVertexes || v2 < 0 || v2 >= numVertexes)
		{
			return false;
		}
		else
		{
			return edgesMatrix[v1][v2];
		}
	}
	bool insertVertex(const V& value);
	bool insertEdge(const int v1, const int v2, const W& weight);
	bool getFirstNeighbor(const int v1, int& v);
	bool getNextNeighbor(const int v1, const int w, int& v);
    
	bool inputVertexesFromFile(ifstream& fin); //从文件中读取点集
	bool inputEdgesFromFile(ifstream& fin); //从文件中读取边集
	void outputGraph();
	
	//深度遍历
	void DFS(GraphMtx& G , const V& v);
	void BFS(GraphMtx& G, const V&v);
private:
	int numVertexes;  //当前的节点数
	int numEdges; //当前的边数
	int maxVertexes; //最大的节点数
	GraphType graphType;
	W maxWeight; //最大的权值，用来表示两个顶点之间是不邻接的
	V* vertexesList; //定点的列表
	W** edgesMatrix;   //边的邻接矩阵
	bool  getVertex(const V value, int& pos) //查找并返回值为Value的顶点的位置
	{
		int i = 0;
		for (i; i < numVertexes; i++)
		{
			if (value == vertexesList[i])
			{
				pos = i;
				return true;
			}

		}
		if (i >= numVertexes)
		{ 
			pos = -1;
			return false;
		}
			
	}
	void DFS( GraphMtx& G, const int & v,bool* visted);

};

template<class V,class W>
GraphMtx<V, W>::GraphMtx(W max, GraphType type, int maxV ):maxWeight(max),maxVertexes(maxV),graphType(type)
{
	numVertexes = 0;
	numEdges = 0;
    //创建顶点的数组
    vertexesList = new V[maxVertexes];  
	if (vertexesList == nullptr)
	{
		cout << "内存申请失败";
		exit(1);
	}
	for (int i = 0; i < maxVertexes;i++)
		vertexesList[i] = 0;   //初始化
    
	//初始化边的邻接矩阵
	edgesMatrix = new W*[maxVertexes];
	if (edgesMatrix == nullptr)
	{
		cout << "内存申请失败";
		exit(1);
	}
	for (int i = 0; i < maxVertexes; i++)
	{
		edgesMatrix[i] = new W[maxVertexes];
		if (edgesMatrix[i] == nullptr)
		{
			cout << "内存申请失败" << endl;
			exit(1);
		}
	}

	//初始化
	for (int i = 0; i < maxVertexes; i++)
	{
		for (int j = 0; j < maxVertexes; j++)
		{
			if (i == j)
			{
				edgesMatrix[i][j] = 0;
			}
			else
			{
				edgesMatrix[i][j] = maxWeight;
			}
			//edgesMatrix[i][j] = (i == j ? 0 : maxWeight);  //这个地方为什么不直接全部都初始化为maxWeight呢
		}
	}
	
	
}
template<class V, class W>
GraphMtx<V, W>::~GraphMtx()
{
	if (vertexesList != nullptr)
	{
		delete[] vertexesList;
		vertexesList = nullptr;
	}
	if (edgesMatrix != nullptr)
	{
		for (int i = 0; i < maxVertexes; i++)
		{
			if (edgesMatrix[i] != nullptr)
			{
				delete[] edgesMatrix[i];
				edgesMatrix[i] = nullptr;
			}
		}
		delete[] edgesMatrix;
		edgesMatrix = nullptr;
	}
}

template<class V, class W>
bool GraphMtx<V,W>::insertVertex(const V& value)
{
	if (numVertexes >= maxVertexes)  //如果超出范围了
	{
		return false;
	}
	else
	{
		vertexesList[numVertexes++] = value;
		return true;
	}
}
template<class V, class W>
bool GraphMtx<V,W>::insertEdge(const int v1, const int v2, const W& weight)
{
	if(v1 < 0 || v1 >= numVertexes || v2 < 0 || v2 >= numVertexes)
	{
		return false;
	}
	else
	{
		if (edgesMatrix[v1][v2] != maxWeight )   // 如果这两个顶点之间已经存在边
		{
			cout << "这v1 与v2 之间已经有边存在了，无法插入边" << endl;
			return false;
		}
		else
		{
			edgesMatrix[v1][v2] = weight;
			numEdges++;   //边的数目+1
			return true;
		}
	}
}
template<class V, class W>
bool GraphMtx<V, W>::getFirstNeighbor(const int v1, int& v)
{
	int i = 0;
	for (i; i < numVertexes; i++)
	{
		if (edgesMatrix[v1][i] != maxWeight && edgesMatrix[v1][i] != 0)  //如果权值不为无限大
		{
			v = i; 
			return true;
		}
	}
	if (i >= numVertexes)
	{
		v = -1;
		return false;
	}
}

template<class V, class W>
bool GraphMtx<V, W>::getNextNeighbor(const int v1, const int w, int& v)
{
	int i = w+1;
	for (i; i < numVertexes; i++)
	{
		if (edgesMatrix[v1][i] != maxWeight && edgesMatrix[v1][i]!=0)  //如果权值不为无限大
		{
			v = i;
			return true;
		}

	}
	if (i >= numVertexes)
	{
		v = -1;
		return false;
	}
}
template<class V, class W>
bool  GraphMtx<V, W>::inputVertexesFromFile(ifstream& fin) //从文件中读取点集
{
	int nums;   //点集的数目
	V tempV; //临时变量
	fin >> nums;  //读入点集的数目
	if (isGraphFull())
	{
		cout << "点击的数目过多，大于图所允许的最大数目,读取失败" << endl;
		return false;
	}
	for (int i = 0; i < nums; i++)
	{
		fin >> tempV;
		if (!insertVertex(tempV))  //如果插入失败的话
		{
			return false;   
		}
	}
	return true;
}
template<class V, class W>
bool GraphMtx<V,W>::inputEdgesFromFile(ifstream& fin) //从文件中读取边集
{
	int nums; //边集的数目
	V v1, v2; //两个点
	W weight; //权值 
	fin >> nums;
	if (isGraphFull())
	{
		cout << "边的数目过多，插入边集失败" << endl;
		return false;
	}
	else
	{
		for (int i = 0; i < nums; i++)
		{
			fin >> v1 >> v2 >> weight;
			int x1, x2;
			if (!(getVertex(v1, x1) && getVertex(v2, x2)))
			{
				return false;
			}
			else
			{
				if (graphType == DIRECTED)  //如果是有向图的话
				{
					if (!insertEdge(x1, x2, weight))
						return false;
				}
				else  //如果是无向图的话
				{
					bool isFind1 = insertEdge(x1, x2, weight);
					bool isFind2 = insertEdge(x2, x1, weight);
					if(!(isFind1||isFind2))
						return false;
				}
			}
		}
		return true;
    }
}
template<class V, class W>
void  GraphMtx<V, W>::outputGraph()
{
	const int place = 4; //占位符的长度
	if (isGraphEmpty())
	{
		cout << "图为空图" << endl;
		return;
	}
	cout << "图的邻接矩阵为：" << endl;
	//打印第一行
	cout << setw(place) << '|';
	for (int i = 0; i < numVertexes; i++)
	{
		cout << setw(place) << vertexesList[i];
	}
	cout << endl;
	//打印第二行
	cout << setw(place) << '|';
	for (int i = 0; i < numVertexes; i++)
	{
		cout << "____";
	}
	cout << endl;
	//打印接下来的行
	for (int i = 0; i < numVertexes; i++)
	{
		cout << vertexesList[i] << setw(place - 1) << '|';
		for (int j = 0; j < numVertexes; j++)
		{
			if (edgesMatrix[i][j] != maxWeight)
			{
				cout << setw(place) << edgesMatrix[i][j];
			}
			else
			{
				cout <<setw(place)<<" ";
			}
		}
		cout << endl;
	}
}
template<class V, class W>
void  GraphMtx<V, W>::DFS( GraphMtx& G, const V& v)
{
	int num = G.numVertexes;
	//先构造一个辅助数组
	bool* visited = new bool[num];
	//初始化
	for (int i = 0; i < num; i++)
	{
		visited[i] = false;
	}

	//获取顶点的坐标
	int loc;
	if (!G.getVertex(v, loc))
	{
		cout << "没有找到顶点" << v << endl;
		return;
	}
	DFS(G, loc, visited);
	cout << endl;
	//判断是不是所有的都遍历一遍了
	for (int i = 0; i < num; i++)
	{
		if (visited[i] == false)  //如果这个点没有被遍历那么就接着从这个点开始继续遍历
		{
			DFS(G, i, visited);
			cout << endl;
		}
	}






	delete[]visited;

	//

}

template<class V,class W>
void  GraphMtx<V, W>::DFS( GraphMtx& G, const int& vLoc, bool* visited)
{
	//在这个函数中顶点v是没有被访问的
	
	//先访问顶点v
	V tempValue;
	if (!G.getVertexValue(vLoc, tempValue))
	{
		cout << "顶点的vloc的值非法" << endl;
		return;
	}
	visited[vLoc] = true;
	//输出值
	cout << tempValue;
    
	//获取其第一个邻接点的位置
	int nextLoc;
	bool isFind = G.getFirstNeighbor(vLoc, nextLoc);  //递归结束的条件
	while (isFind)
	{
		int tempLoc = nextLoc;
		if (visited[nextLoc] == false) //如果没有访问过
		{
			//输出没有访问过的路径
			G.getVertexValue(nextLoc, tempValue);
			cout << "->";
			DFS(G, nextLoc, visited);
		}
		else
		{
			G.getVertexValue(nextLoc, tempValue);
			cout << "->(" << tempValue << ")";
		}
		isFind = G.getNextNeighbor(vLoc,tempLoc, nextLoc);
	}
	return;
	
}

template<class V,class W>
void GraphMtx<V, W>::BFS(GraphMtx& G, const V&v)
{
	//建立辅助数组
	int num = G.numVertexes;
	//先构造一个辅助数组
	bool* visited = new bool[num];
	//初始化
	for (int i = 0; i < num; i++)
	{
		visited[i] = false;
	}
	int loc;
	if (!G.getVertex(v,loc))
	{
		cout << "没有找到顶点" << v<<" 广度遍历退出" << endl;
		return;
	}
	//访问节点v
	visited[loc] = true;
	cout<< v ;

	//执行广度遍历
	SeqQueue<int>Q;   //申请一个队列
	//先获取v的第一个邻接节点
	if(!Q.enQueue(loc))
		return ;
   //队列里还为空
	while (!Q.isEmpty())
	{
		int FoundLoc;  //取出已经找到的节点，准备进行广度遍历
		Q.deQueue(FoundLoc);
		int nextLoc;
		bool isFoundNext=G.getFirstNeighbor(FoundLoc, nextLoc);
		if (isFoundNext)  //第一个邻接节点
		{
			//访问
			V tempValue;
			if (visited[nextLoc] == false)
			{
				if(!Q.enQueue(nextLoc))
					return ;  //入列
				visited[nextLoc] = true;
				G.getVertexValue(nextLoc, tempValue);
				cout << "->" << tempValue ;
			}
			else
			{
				//输出路径
				G.getVertexValue(nextLoc, tempValue);
				cout << "->(" << tempValue << ")";
			}
			int tempLoc = nextLoc;  //临时变量
			isFoundNext = G.getNextNeighbor(FoundLoc, tempLoc, nextLoc);
			while (isFoundNext)   //遍历之后的邻接节点
			{
				//如果找到的话
				//访问
				if (visited[nextLoc] == false)
				{
					if(!Q.enQueue(nextLoc))
						return ;  //入列
					visited[nextLoc] = true;
					G.getVertexValue(nextLoc, tempValue);
					cout << "->" << tempValue ;
				}
				else
				{
					//输出路径
					G.getVertexValue(nextLoc, tempValue);
					cout << "->(" << tempValue << ")";
				}
				tempLoc = nextLoc;
				isFoundNext = G.getNextNeighbor(FoundLoc, tempLoc, nextLoc);
			}
			//把所有的邻接节点都放问过了，就跳出循环取出队列中的节点
		}
		if (Q.isEmpty())   //如果队列是空的
		{
			cout << endl;
			for (int i = 0; i < num; i++)
			{
				if (visited[i] == false)  //如果还有点没有被遍历，那么访问这个点并且将其入列
				{
					visited[i] = true;
					V tempV;
					G.getVertexValue(i, tempV);
					cout << tempV;
					if(!Q.enQueue(i))
						return ;
					break;
				}
			}
		}
	}
     

	
}
#endif // !GRAPHMTX_H
#pragma once
