#include "SyntaxTree.h"



SyntaxTree::SyntaxTree()
{
	head = int(nodes.size()-1);
}


SyntaxTree::~SyntaxTree()
{
}
int SyntaxTree::addNode(treeNode& t) {
	nodes.push_back(t);
	head = nodes.size() - 1;  // 默认指向最后一个位置，适用于递归建树
	return head;             // 返回指向刚刚加入的node的 位置，方便建树
}
void  SyntaxTree::outputTreeAsFile(ofstream& fout,int  subTree , int widthset , int heightset ) {
	queue<treeNode> treeNodeQueue;              //利用队列进行深度遍历
	vector<pair<treeNode,int>> currentNodes;

	int depth = getTreeDepth(subTree);
	//根节点
	if (nodes[subTree].child_ptrs.size() > 1) {
		fout << setiosflags(ios::left) << setw(widthset)<<setfill('-') << nodes[subTree].t.get_token_name() << setw(' ')<<endl;
	}
	else {
		fout << setiosflags(ios::left) << setw(widthset) << nodes[subTree].t.get_token_name() << endl;
	}
	// 把根节点的孩子入队列
	if (nodes[subTree].child_ptrs.size() == 0) {
		// 如果没有孩子，需要补空检点
		treeNode t = treeNode();
		t.width = nodes[subTree].width;              // -1表示是空节点
		treeNodeQueue.push(t);
	}
	else {
		for (int j = 0; j < nodes[subTree].child_ptrs.size(); j++) {
			treeNodeQueue.push(nodes[nodes[subTree].child_ptrs[j]]);
		}
	}
	// 跟节点之后的
	for (int h = 0; h < depth-1; h++) {
		//把队列里需要打印的节点转移到vector中,同时计算需要打印的横树枝的宽度
		//见vector清空
		currentNodes.clear();
		while(treeNodeQueue.size()>0) {
			int printwidth = 0;
			treeNode n = treeNodeQueue.front(); 
			for (int j = 0; j < int(n.child_ptrs.size() - 1); j++) {           //孩子数 -1
				printwidth += nodes[n.child_ptrs[j]].width;
			}
			currentNodes.push_back(make_pair(treeNodeQueue.front(),printwidth));
			treeNodeQueue.pop();          //队列里弹出节点
		}
		//按深度进行输出
		for (int line = 0; line < heightset; line++) {
			//分行输出
			for (int n = 0; n < currentNodes.size(); n++) {
				//分结点输出
				//输出当前的节点
				pair<treeNode, int> current = currentNodes[n];
				if (line == heightset - 1) {
					//输出本节点内容
					if (current.first.t.get_token_name() == "none") {
						fout << setiosflags(ios::left) << setw(widthset) << " ";
					}
					else if (current.first.t.get_value() == "_") {  //如果token值是非关键字，不需要把值打印出来
						if (current.first.child_ptrs.size() > 1) {
							fout << setiosflags(ios::left) << setw(widthset) << setfill('-') << current.first.t.get_token_name() << setfill(' ');
						}
						else {
							fout << setiosflags(ios::left) << setw(widthset) << current.first.t.get_token_name();
						}
					}
					else {
						if (current.first.child_ptrs.size() > 1) {
							fout << setiosflags(ios::left) << setw(widthset) << setfill('-') << current.first.t.get_token_name() + "=" + current.first.t.get_value() << setfill(' ');
						}
						else {
							fout << setiosflags(ios::left) << setw(widthset)  << current.first.t.get_token_name() + "=" + current.first.t.get_value() ;
						}
					}
					// 输出 ”横树枝“
					for (int i = 0; i < current.first.width-1; i++) {
						//打印该节点所需要的横树枝
						if (current.first.t.get_token_name() == "none") {
							fout << setiosflags(ios::left) << setw(widthset) << " ";
						}
						else if (i < current.second-1) {
							fout << setiosflags(ios::left) << setw(widthset)<<setfill('-') << "-" << setfill(' ');           //打印横树枝

						}
						else {
							fout << setiosflags(ios::left) << setw(widthset) << " ";
						}
					}
				}
				// 输出 "纵树枝"
				else {
					for (int i = 0; i  < current.first.width; i++) {
						if (current.first.t.get_token_name() == "none") {
							fout << setiosflags(ios::left) << setw(widthset) << " ";
							continue;
						}
						if (i == 0) {
							fout << setiosflags(ios::left) << setw(widthset) << "|";
						}
						else {
							fout << setiosflags(ios::left) << setw(widthset) << " ";
						}
					}
				}
			}
			fout << endl;
		}
		// 计算下一层需要输出的节点
		while(treeNodeQueue.size()>0){
			treeNodeQueue.pop();
		}
		for (int i = 0; i < currentNodes.size(); i++) {
			if (currentNodes[i].first.child_ptrs.size() == 0) {
				// 如果没有孩子，需要补空检点
				treeNode t = treeNode();
				t.width = currentNodes[i].first.width;              // -1表示是空节点
				treeNodeQueue.push(t);
			}
			else {
				for (int j = 0; j < currentNodes[i].first.child_ptrs.size(); j++) {
					treeNodeQueue.push(nodes[currentNodes[i].first.child_ptrs[j]]);
				}
			}
		}
	}	
}
int  SyntaxTree::getTreeWidth( int subTree) {  //计算树的宽度，最宽的节点数
	int width = 0;
	if (nodes[subTree].child_ptrs.size() == 0) {
		//如果是叶子节点
		width = 1;
		nodes[subTree].width = width;
		return 1;    //出口条件
	}
	for (int i = 0; i < nodes[subTree].child_ptrs.size(); i++) {
		width += getTreeWidth(nodes[subTree].child_ptrs[i]);  //递归计算宽度
	}
	nodes[subTree].width = width;
	return width;
}

int SyntaxTree::getTreeDepth(int subTree) {  //计算树的深度
	int depth = 0;
	if (nodes[subTree].child_ptrs.size() == 0) {
		//如果是叶子节点
		return 1;    //出口条件
	}
	int maxDepth = 0;
	for (int i = 0; i < nodes[subTree].child_ptrs.size(); i++) {
		int subDepth = getTreeDepth(nodes[subTree].child_ptrs[i]);  //递归计算宽度
		if (subDepth > maxDepth) {
			maxDepth = subDepth;
		}
	}
	return maxDepth+1;
}