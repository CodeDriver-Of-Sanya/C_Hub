#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>

#define ROW 10
#define COL 10

struct myPoint {
	int row, col;
};

struct treeNode
{
	struct myPoint p;					//当前节点坐标
	struct treeNode* parentNode;		//指向父节点
	struct treeNode* children[4];		//四个孩子
	int curSize;				//已存孩子个数

};

//四个方向（没有顺序要求）
enum dir
{
	p_up,
	p_down,
	p_left,
	p_right
};

//创建节点函数
struct treeNode* createNode(int row, int col) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->p.row = row;
	pNew->p.col = col;
	return pNew;
}

//判断是否能走
bool canWalk(struct myPoint p, int map[ROW][COL], bool isGoneMap[ROW][COL]) {
	//越界
	if (p.row >= ROW || p.row < 0 ||
		p.col >= COL || p.col < 0) {
		return false;
	}
	//墙
	if (map[p.row][p.col])return false;
	//走过
	if (isGoneMap[p.row][p.col])return false;

	return true;
}

/*
深度寻路算法：
	逐个试探：
		试探方向有个顺序：
			一般 上右下左
		每个节点都记录当前试探方向 和 是否走过
	循环找到当前点周围四个方向的试探点检测能不能走
		检测完就将检测点转到下一个方向
		能走：向该方向走一步，将当前位置坐标记录入栈，并将当前位置标记为走过
		不能走：前三个不能走没有其他操作
			最后一个不能走：就是走到死胡同了，退栈，让当前位置变为新的栈顶坐标
		找到终点：当前位置为终点位置
		找不到终点：栈空了

广度寻路算法：
	从当前点开始，构建一颗 四叉树（只能四个方向走，上下左右）
	一层一层去拓展，直到遇见终点 或者 下一层
		当前层一个数组，下一层一个数组，数组切换就是层次切换
			找到终点：数组里出现终点
			找不到：数组里一个点都没有
*/

int main() {
	//地图
	int map[ROW][COL] = {
		{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 1 },
		{ 0, 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 0, 1, 0, 1, 1, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
		{ 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 }
	};
	//起点
	struct myPoint begP = { 0,0 };
	//终点
	struct myPoint endP = { 3,9 };
	//标记是否走过的地图
	bool isGoneMap[ROW][COL] = { 0 };
	//但是首先要标记起点走过
	isGoneMap[begP.row][begP.col] = true;

	//创建树,让起点成为树的根节点
	struct treeNode* treeRoot = createNode(begP.row, begP.col);

	//当前层(从起点开始)
	struct treeNode* curFloor[100] = {treeRoot};
	int curFSize = 1;
	//下一层
	struct treeNode* nextFloor[100];
	int nextFSize = 0;

	struct treeNode* pTemp = NULL;
	struct treeNode* cur = NULL;

	//终点标记
	bool isFind = false;

	while (true)
	{
		//开始一层层推进
		for (int i = 0; i < curFSize; i++)
		{
			cur = curFloor[i];
			//找出下一层所有节点
			for (int j = 0; j < 4; j++)
			{
				//当前节点的四个方向
				pTemp = createNode(cur->p.row, cur->p.col);
				//根据方向改temp
				switch (j)
				{
				case p_up:
					pTemp->p.row--;
					break;
				case p_down:
					pTemp->p.row++;
					break;
				case p_left:
					pTemp->p.col--;
					break;
				case p_right:
					pTemp->p.col++;
					break;
				}
				//判断能不能走
				if (canWalk(pTemp->p,map,isGoneMap)) {
					//能走
					//入树
					pTemp->parentNode = cur;
					cur->children[cur->curSize++] = pTemp;
					//入下一层数组
					nextFloor[nextFSize++] = pTemp;
					//标记走过
					isGoneMap[pTemp->p.row][pTemp->p.col] = true;
					//判断是否找到终点
					if (endP.row == pTemp->p.row &&
						endP.col == pTemp->p.col) {
						isFind = true;
						break;
					}
				}
				else {
					//不能走
					free(pTemp);
					pTemp = NULL;
				}
				
			}
			if (isFind)break;
		}
		if (isFind)break;

		//如果下一层里面什么都没有,直接跳出循环，不用找了
		if (nextFSize == 0)break;

		//切换到下一层
		memcpy(curFloor, nextFloor,nextFSize * sizeof(struct treeNode));
		curFSize = nextFSize;
		//将下一层的容器清空
		memset(nextFloor, 0, nextFSize * sizeof(struct treeNode));
		nextFSize = 0;
	}

	if (isFind) {
		printf("找到终点了！\n");
		while (pTemp)
		{
			printf("(%d,%d)\n", pTemp->p.row, pTemp->p.col);
			pTemp = pTemp->parentNode;
		}
	}
	else {
		printf("找不到终点！\n");
	}

	while (true);

	return 0;
}
