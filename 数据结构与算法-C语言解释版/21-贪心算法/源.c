#include<stdio.h>
#include<malloc.h>

//代表不连通
#define NO 0xFFFFFF

#define MAX 100
/*
贪心（贪婪）算法思想：
	大的问题归纳成小的问题，然后迭代
	每一小步就选择当前看来最好的选择，如此反复，试图得到整体最优解
	类似于学过的A星寻路
		缺陷：
			1.并非一定能得到整体最优解
			2.每一步都是局部最优
	主要解决什么问题：
		1.最短路径问题
			迪杰斯特拉(Dijkstra)算法：求起点到终点的最短路径
				通过不断选择距离最近的顶点来逐渐扩大最短路径权值（代价），直到覆盖所有顶点
		2.最小生成树问题
			克鲁斯卡尔(Kruskal)算法：图结构 转化成二叉树，按照权重最小来添加
				1 对所有的边按照权重大小排序
				2 从小到大依次添加到最小生成树中
					注意不能产生回环（回路）
					如果会产生回环，就跳过这条边
				3 最终所有的边都添加到了树中，此时这棵树就叫做这个图对应的最小生成树
		3.背包问题
*/

//图结构
struct graph {
	int verNum;//顶点数量
	int edgeNum;//边数量
	char vertex[MAX];//存顶点的
	int edge[MAX][MAX];//存边的
};

void Dijkstra(struct graph* g, int in, int dist[MAX]) {
	//1 找到当前入口到其他顶点的路径

	//标记成功获取的路径(0=没获取，1=成功获取)
	int flag[MAX] = { 0 };
	for (int i = 0; i < g->verNum; i++)
	{
		flag[i] = 0;
		//存入从入口到每个顶点的值
		dist[i] = g->edge[in][i];
	}

	//2 扩充顶点
	flag[in] = 1;//入口标记
	dist[in] = 0;


	int min = NO;
	int minIdx;

	for (int i = 1; i < g->verNum; i++) {
		min = NO;
		for (int j = 1; j < g->verNum; j++) {
			if (0 == flag[j] && dist[j] < min) {
				min = dist[j];
				minIdx = j;
			}
		}
		
		flag[minIdx] = 1;
		for (int j = 1; j < g->verNum; j++) {
			if (0 == flag[j] && (g->edge[minIdx][j])<dist[j]) {
				dist[j] = min + g->edge[minIdx][j];
			}
		}

	}
	for (int i = 1; i < g->verNum; i++) {
		printf("最短路径(%c,%c)=%d\n",
			g->vertex[in],
			g->vertex[i],
			dist[i]);
	}
}

//边
struct edge {
	int beg;
	int end;
	int value;//权重
};

void travel(struct edge* a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d->%d  %d\n",
			a[i].beg, a[i].end, a[i].value);
	}
}

void Kruskal(struct graph* g) {
	//1 把所有的边都找出来
	struct edge* pEdges = malloc(g->edgeNum * sizeof(struct edge));
	
	int k = 0;
	for (int i = 0; i < g->verNum; i++) {
		for (int j = 0; j < i; j++)//因为是无向图，二维数组中对称，所以只用遍历一半就行了
		{
			if (NO != g->edge[i][j]) {
				pEdges[k].beg = g->vertex[i] - '0';
				pEdges[k].end = g->vertex[j] - '0';
				pEdges[k].value = g->edge[i][j];
				k++;
			}
		}
	}
	//travel(pEdges, k);
	//2  并排序
	int minV;
	struct edge temp;

	//插入排序
	for (int i = 0; i < k; i++)
	{
		minV = i;//假设第一个最小
		for (int j = i; j < k; j++) {
			if (pEdges[j].value < pEdges[minV].value)
				minV = j;
		}

		//pEdges[i] 和 pEdges[minV]  交换
		temp.beg = pEdges[minV].beg;
		temp.end = pEdges[minV].end;
		temp.value = pEdges[minV].value;


		pEdges[minV].beg = pEdges[i].beg;
		pEdges[minV].end = pEdges[i].end;
		pEdges[minV].value = pEdges[i].value;


		pEdges[i].beg = temp.beg;
		pEdges[i].end = temp.end;
		pEdges[i].value = temp.value;
	}
	//travel(pEdges, k);

	//3 循环添加到最小生成树中，如果产生回环，就不添加
	struct edge* minTree = malloc(g->edgeNum * sizeof(struct edge));

	//每个顶点配置一个标记值
	int flag[MAX] = { 0 };
	for (int i = 0; i < g->verNum; i++) {
		flag[i] = i;
	}

	int beg, end;
	int num = 0;
	int elem;
	for (int i = 0; i < g->edgeNum; i++)
	{
		//找到当前边的两个顶点 对应  flag数组下标
		beg = pEdges[i].beg - 1;
		end = pEdges[i].end - 1;
		printf("beg:%d,end:%d\n", beg, end);

		//如果顶点位置存在 并且顶点的标记值不同  就不会产生回路
		if (flag[beg] != flag[end]) {
			//添加到最小生成树中
			minTree[num].beg = pEdges[i].beg;
			minTree[num].end = pEdges[i].end;
			minTree[num].value = pEdges[i].value;

			num++;//计数

			elem = flag[end];

			//把新加到最小生成树中的顶点标记改成一样的
			for (int k = 0; k < g->verNum; k++) {
				if (flag[k] == elem)
					flag[k] = flag[beg];
			}

			printf("flag:");
			for (int j = 0; j < g->verNum; j++) {
				printf("%d ", flag[j]);
			}
			printf("\n");

			//如果选择的边的数量和顶点数相差1，结束
			if (num == g->verNum - 1) break;
		}
	}
	printf("最小生成树:");
	travel(minTree, num);
}



int main() {
	//Dijkstra
	struct graph g1 =
	{
		5,7,"ABCDE",
		{
			{ 0, 10, NO, 30, 100 },
			{ NO, 0, 50, NO, NO },
			{ NO, NO, 0, NO, 10 },
			{ NO, NO, 20, 0, 60 },
			{ NO, NO, NO, NO, 0 },
		}
	};
	//入口 顶点数组中的下标
	//int in = 0;

	//数组 存放路径
	//int dist[MAX] = { 0 };

	//Dijkstra(&g1, in, dist);
	//printf("path:");
	//for (int i = 0; i < 10; i++)
		//printf("%d ", dist[i]);
	//printf("\n");

	//Kruskal
	struct graph g2 = {
		7, 9, "1234567",
		{
			{ 0, 6, NO, NO, NO, 1, NO },
			{ 6, 0, 4, NO, NO, NO, 3 },
			{ NO, 4, 0, 2, NO, NO, NO },
			{ NO, NO, 2, 0, 6, NO, 5 },
			{ NO, NO, NO, 6, 0, 8, 7 },
			{ 1, NO, NO, NO, 8, 0, NO },
			{ NO, 3, NO, 5, 7, NO, 0 }
		}
	};

	Kruskal(&g2);

	while (1);
	return 0;
}
