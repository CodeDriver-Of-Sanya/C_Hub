#include<iostream>
#include<limits>//numeric_limits 容器
#include<vector>
#include<queue>

using namespace std;

//节点类
class Node
{
public:
	int index;		//序号
	int weight;		//权重

	//构造
	Node(int index = 0,int weight = 0):index(index),weight(weight){}
	//拷贝构造
	Node(const Node& n):index(n.index),weight(n.weight){}

	//重载 < 运算符
	friend bool operator<(const Node& one, const Node& two) {
		return one.weight > two.weight;
	}

};

//路径类
class Path
{
public:
	int index;		//序号
	int weight;		//权重

	Path():index(0),weight(numeric_limits<int>::max()){}

};

//最短路径类
class shortPath {
public:
	vector<vector<int>> graph;	//图
	int nodeCnt;	//节点统计
	const int start;	//起始
	const int end;		//结束
	//存储最短路径的容器
	vector<int> pathIdx;
	int shortPathValue;	//最短路径值
public:
	shortPath(const vector<vector<int>>& g,
		int end):start(-1),end(end),
		nodeCnt(g.size()),graph(g){}

	//打印
	void printPath() {
		cout << "最短路径值:" << shortPathValue << endl;
		cout << "路径:";
		copy(pathIdx.rbegin(), pathIdx.rend(),
			ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	void getShortPath() {
		//初始化路径容器大小
		vector<Path> myPath(nodeCnt);

		//优先队列
		priority_queue<Node, vector<Node>> minHeap;//最小堆

		//入口放到队列中
		minHeap.push(Node(0, 0));

		while (true)
		{
			//获取队列头并将其从队中移除
			Node top = minHeap.top();
			minHeap.pop();

			//如果找到了终点，循环结束
			if (end == top.index)break;

			//剪枝 合适的放进来，不合适的不要
			for (int i = 0; i < nodeCnt; i++)
			{
				if (graph[top.index][i] != start &&
					top.weight + graph[top.index][i] < myPath[i].weight) {

					minHeap.push(
						Node(i, top.weight + graph[top.index][i])
					);
					myPath[i].index = top.index;
					myPath[i].weight = top.weight + graph[top.index][i];
				}
			}

			//堆空了，也要结束
			if (minHeap.empty())break;

		}
		shortPathValue = myPath[end].weight;

		//求路径
		int index = end;
		pathIdx.push_back(index);
		                                          
		while (true)//从终点反向去找起点
		{
			index = myPath[index].index;
			pathIdx.push_back(index);
			if (0 == index)break;//找到起点，结束
		}
	}
};

int main() {
	//准备图
	const int size = 11;

	vector<vector<int>> graph(size);

	//开内存
	for (int i = 0; i < size; i++) {
		graph[i].resize(size);
	}
	//初始化
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			graph[i][j] = -1;
		}
	}

	graph[0][1] = 2;
	graph[0][2] = 3;
	graph[0][3] = 4;

	graph[1][2] = 3;
	graph[1][4] = 7;
	graph[1][5] = 2;

	graph[2][5] = 9;
	graph[2][6] = 2;


	graph[3][6] = 2;

	graph[4][7] = 3;
	graph[4][8] = 3;

	graph[5][6] = 1;
	graph[5][8] = 3;

	graph[6][8] = 5;
	graph[6][9] = 1;

	graph[7][10] = 3;

	graph[8][10] = 2;

	graph[9][10] = 2;
	graph[9][8] = 2;

	shortPath sPath(graph, 10);

	sPath.getShortPath();

	sPath.printPath();

	while (1);
	return 0;
}
