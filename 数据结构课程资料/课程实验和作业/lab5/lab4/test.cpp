#include<iostream>
#include"GraphMtx.hpp"
int main()
{
	
	GraphMtx<char, int> myUGraph(100,GraphMtx<char,int>::UNDIRECTED);
	GraphMtx<char,int> myGraph(100, GraphMtx<char, int>::DIRECTED);
	ifstream finV;
	//读入顶点集
	finV.open("vertexes.txt", ios::in);
	if (!finV.is_open())
	{
		cout << "点集文件读取失败！" << endl;
		exit(1);
	}
	else
	{
		myGraph.inputVertexesFromFile(finV);
	}
	finV.close();
	ifstream finE;
	finE.open("edges.txt", ios::in);
	if (!finE.is_open())
	{
		cout << "边集文件读取失败！" << endl;
		exit(1);
	}
	else
	{
		myGraph.inputEdgesFromFile(finE);
	}
	finE.close();

	ifstream finUV;
	finUV.open("vertexes.txt", ios::in);
	if (!finUV.is_open())
	{
		cout << "点集文件读取失败！" << endl;
		exit(1);
	}
	else
	{
		myUGraph.inputVertexesFromFile(finUV);
	}
	finUV.close();

	ifstream finUE;
	finUE.open("edges.txt", ios::in);
	if (!finUE.is_open())
	{
		cout << "边集文件读取失败！" << endl;
		exit(1);
	}
	else
	{
		myUGraph.inputEdgesFromFile(finUE);
	}
	finUE.close();
	//输出邻接矩阵
	cout << "有向图测试：" << endl;
	myGraph.outputGraph();
	cout << "有向图深度遍历：" << endl;
	myGraph.DFS(myGraph, 'c');
	cout << endl;
	cout << "有向图广度遍历：" << endl;
	myGraph.BFS(myGraph, 'c');
	cout << endl;

	cout<<"无向图测试" << endl;
	myUGraph.outputGraph();
	cout << "无向图深度遍历：" << endl;
	myUGraph.DFS(myUGraph, 'c');
	cout << endl;
	cout << "无向图广度遍历：" << endl;
	myUGraph.BFS(myUGraph, 'c');
	
	system("pause"); 
	return 0;
}