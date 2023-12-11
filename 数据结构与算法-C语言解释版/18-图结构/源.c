#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define VERTEXS 7
#define EDGES 8

/*
* 07
* 
图：
	由 顶点 和 边 组成
	顶点：存数据，例如树结构的子树，链表中的节点一样
	边：描述顶点之间的关系
图的分类：
	有向图：边有方向（单向连通）
	无向图：边没有方向（双向连通）
	网图：边有数值，不仅表连通关系，还有区别，这个数值也被称作 权重
如何描述图：有很多种方式
	临接矩阵：数组 二维数组

	临接表：链表
图的遍历：
	深度优先遍历：Deap First Search(DFS)
					和深度寻路算法思想差不多
					一路找下一个节点，找不到就换路线
	广度优先遍历：Breadth First Search(BFS)
					和广度寻路算法思想一致
					先把相邻的都找完，找完了再找下一层相邻的
*/

//用 临接矩阵 描述 图

//图的类型
struct Graph
{
	//顶点个数
	int vertexs;
	//边的条数
	int edges;
	//指针，指向 存储顶点的 指针
	char* pVertex;
	//指针，指向 存储边的 二级指针
	int** pEdge;
};

//创建图对象
struct Graph* createGraph() {
	struct Graph* pNew = malloc(sizeof(struct Graph));
	if (NULL == pNew)return NULL;
	//置空
	memset(pNew, 0, sizeof(struct Graph));
	//返回出去
	return pNew;
}

//初始化图对象
void initGraph(struct Graph* g, char* buff,int map[VERTEXS][VERTEXS]) {
	if (NULL == g || NULL == buff)return;

	//1.开内存
	g->vertexs = VERTEXS;
	g->edges = EDGES;

	g->pVertex = malloc(sizeof(char) * g->vertexs);		//一维数组存所有的顶点
	memcpy(g->pVertex, buff, sizeof(char) * g->vertexs);//2.赋值
	g->pEdge = malloc(g->vertexs * sizeof(int*));		//动态内存分配出二维数组
	for (int i = 0; i < g->vertexs; i++)
	{
		g->pEdge[i]=malloc(g->vertexs * sizeof(int));
		memcpy(g->pEdge[i], map[i], g->vertexs * sizeof(int));//2.赋值
	}
}

//显示图对象
void showGraph(struct Graph* g) {
	//双层循环打印，要多一行多一列用于显示顶点名字
	for (int i = 0; i < g->vertexs+1; i++)
	{
		for (int j = 0; j < g->vertexs + 1; j++)
		{
			if (0 == i && 0 == j) {
				printf("  ");
			}
			else if (0 == i) {//第1行打印顶点名字
				printf("%c ", g->pVertex[j-1]);
			}
			else if (0 == j) {//第1列打印顶点名字
				printf("%c ", g->pVertex[i-1]);
			}
			else {//中间部分
				printf("%d ", g->pEdge[i - 1][j - 1]);
			}
		}
		printf("\n");
	}
}

//从g指向的图中找到顶点v在数组中的下标 找不到返回-1
int _getIdx(struct Graph* g, char v) {
	if (NULL == g) return -1;
	for (int i = 0; i < g->vertexs; i++) {
		if (v == g->pVertex[i]) return i;
	}
	return -1;
}

//找某个顶点的第一个相邻顶点，找到了返回其下标，没找到返回-1，辅助数组标记有没有找过
int _findFirstVertex(struct Graph* g, int begIdx, bool isFind[VERTEXS]) {
	for (int i = 0; i < g->vertexs; i++)
	{
		if (isFind[i])continue;//已经找过了的跳过

		if (1 == g->pEdge[begIdx][i])return i;
	}
	return -1;
}
//找某个顶点的第二个相邻顶点，找到了返回其下标，没找到返回-1，辅助数组标记有没有找过
int _findNextVertex(struct Graph* g, int begIdx, bool isFind[VERTEXS]) {
	//把当前点跳过，从下一个开始找
	for (int i = begIdx+1; i < g->vertexs; i++)
	{
		if (isFind[i])continue;//已经找过了的跳过

		if (1 == g->pEdge[begIdx][i])return i;
	}
	return -1;
}

//深度优先搜索
void DFS(struct Graph* g, char beg, bool isFind[VERTEXS]) {
	//找beg顶点的第一个相邻的顶点x,然后找x的第一个相邻顶点y

	//当前位置
	int curIdx = _getIdx(g, beg);
	//记录当前位置已经找过了
	isFind[curIdx] = true;

	//下一个顶点下标
	int nextIdx = _findFirstVertex(g, curIdx, isFind);

	//一路找下一个
	while (true)
	{
		if (-1 == nextIdx)break;
		//输出没找过的（找过的就不重复输出了）
		if (false == isFind[nextIdx]) {
			printf("%c", g->pVertex[nextIdx]);
			//向后递归
			DFS(g, g->pVertex[nextIdx], isFind);
		}
		nextIdx = _findNextVertex(g, curIdx, isFind);
	}
}
//广度优先搜索
void BFS(struct Graph* g, char beg, bool isFind[VERTEXS]) {
	//需要一个队列
	int queue[VERTEXS] = { 0 };
	int queueNum = 0;//队列元素个数

	//第一个入队
	queue[queueNum++] = _getIdx(g, beg);
	//入队就要标记走过
	isFind[_getIdx(g, beg)] = true;

	int headIdx;
	int idx;
	while (queueNum)
	{
		//第一个出队
		headIdx = queue[0];
		queueNum--;
		for (int i = 0; i < queueNum; i++)
		{
			queue[i] = queue[i + 1];
		}

		//第一个相邻的顶点放到队列中
		idx = _findFirstVertex(g, headIdx, isFind);
		while (true)
		{
			if (-1 == idx)break;
			if (false == isFind[idx]) {
				isFind[idx] = true;
				printf("%c ", g->pVertex[idx]);
				queue[queueNum++] = idx;//入队
			}
			idx = _findNextVertex(g, headIdx, isFind);
		}
	}
}

int main() {

	struct Graph* g = NULL;
	//一个数组存所有的顶点
	char buff[7] = "ABCDEFG";
	//二维数组存顶点间关系
	int map[VERTEXS][VERTEXS] = {
		{ 0, 1, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 1, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 0, 0, 0, 0, 0, 0 }
	};
	g = createGraph();
	initGraph(g, buff, map);
	showGraph(g);

	bool isFind[VERTEXS] = { 0 };

	printf("A ");
	//DFS(g, 'A', isFind);
	BFS(g, 'A', isFind);
	printf("\n");
	return 0;
}
