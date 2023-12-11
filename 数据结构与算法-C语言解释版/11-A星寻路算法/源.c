#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>

#define ROW 10
#define COL 10

#define StraightLineCost 10
#define DiagonalCost 14

//方向枚举
enum dir
{
	up,
	down,
	left,
	right,
	l_up,
	l_down,
	r_up,
	r_down
};

//点类型
struct Point
{
	int row, col, f, g, h;
};

//树节点类型
struct treeNode {
	struct Point p;
	struct treeNode* parent;
	struct treeNode* children[8];
	int curSize;
};

//创建树节点的函数
struct treeNode* createTN(struct Point p) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->p.row = p.row;
	pNew->p.col = p.col;
	//注意g要累加
	pNew->p.g = p.g;

	return pNew;
}

//判断点能不能走
bool canWalk(struct Point p, int map[ROW][COL], bool isGone[ROW][COL]) {
	if (p.row < 0 || p.row >= ROW ||
		p.col < 0 || p.col >= COL) return false;

	if (isGone[p.row][p.col])return false;

	if (1 == map[p.row][p.col])return false;

	return true;
}

//计算h
int getH(struct Point now, struct Point dist) {
	int x = dist.row - now.row;
	if (x < 0) {
		x = -x;
	}
	int y = dist.col - now.col;
	if (y < 0) {
		y = -y;
	}

	return (x + y) * StraightLineCost;
}

/*
A星寻路算法：
	对路径进行量化评估：用数字来表示寻路的消耗
	代价：消耗多，代价高；消耗少，代价低
	A星寻路既能走直线，又能走斜线
	每一步的代价都需要自行设置：
		直线10，斜线14
		一般的设置比例  直线：斜线=1：根号2 （源自勾股定理）
		评估代价值（f）= 起点到当前点（试探点）已经付出的代价（g） + 试探点到终点的预估代价（h）
		在预估时要无视障碍物，并且只算直线距离
		走过的点依旧要标为走过
	每一个点因为最多有八个点可以走，所以每个点设置为八叉树结构存储
		同样要有指向父元素的指针，方便找到终点后往回找路径
		再来个数组存所有可能的节点，每次遍历数组找评估代价值最小的点走（走不通的点记得从数组中去除）

*/

int main() {

	//地图
	int map[ROW][COL] = {
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 0, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
	};
	//标记走过地图
	bool isGone[ROW][COL] = { 0 };
	//标记是否找到终点
	bool isFind = false;

	//起点
	struct Point begP = { 1,1 };
	//起点标记为走过
	isGone[begP.row][begP.col] = true;
	//终点
	struct Point endP = { 6,7 };

	//树
	struct treeNode* treeRoot = NULL;
	//起点入树
	treeRoot = createTN(begP);

	//比大小的数组
	struct treeNode* arr[100];
	//有效个数
	int cur = 0;

	//当前点
	struct treeNode* curN = treeRoot;
	//临时点
	struct treeNode* pTemp = NULL;
	//最小值下标记录
	int minIdx;

	//开始寻路
	while (true)
	{
		//遍历当前点周围的点
		for (int i = 0; i < 8; i++)
		{
			pTemp = createTN(curN->p);
			switch (i) {
			case up:
				pTemp->p.row--;
				pTemp->p.g += StraightLineCost;
				break;
			case down:
				pTemp->p.row++;
				pTemp->p.g += StraightLineCost;
				break;
			case left:
				pTemp->p.col--;
				pTemp->p.g += StraightLineCost;
				break;
			case right:
				pTemp->p.col++;
				pTemp->p.g += StraightLineCost;
				break;
			case l_up:
				pTemp->p.col--;
				pTemp->p.row--;
				pTemp->p.g += DiagonalCost;
				break;
			case r_up:
				pTemp->p.col++;
				pTemp->p.row--;
				pTemp->p.g += DiagonalCost;
				break;
			case l_down:
				pTemp->p.col--;
				pTemp->p.row++;
				pTemp->p.g += DiagonalCost;
				break;
			case r_down:
				pTemp->p.col++;
				pTemp->p.row++;
				pTemp->p.g += DiagonalCost;
				break;
			}//switch end

			//判断能不能走
			if (canWalk(pTemp->p,map,isGone)) {
				//能走就要
				//计算h
				pTemp->p.h = getH(pTemp->p, endP);
				//计算f
				pTemp->p.f = pTemp->p.h + pTemp->p.g;
				//入树
				pTemp->parent = curN;
				curN->children[curN->curSize++] = pTemp;
				//入数组
				arr[cur++] = pTemp;
				//但是先不要走
			}
			else {
				//不能走
				free(pTemp);
				pTemp = NULL;
			}

		}//for (int i = 0; i < 8; i++) end
		
		//测试
		//for (int i = 0; i < cur; i++) {
		//	printf("%d:(%d,%d)g:%d h:%d f:%d\n", i, arr[i]->p.row, arr[i]->p.col,arr[i]->p.g,arr[i]->p.h,arr[i]->p.f);
		//}
		
		//从数组中找到 f 最小的点走
		minIdx = 0;//先假设第一个为最小值
		for (int j = 0; j < cur; j++)
		{
			if (arr[j]->p.f < arr[minIdx]->p.f) {
				minIdx = j;
			}
		}
		curN = arr[minIdx];
		//需要在地图中标记走过
		isGone[curN->p.row][curN->p.col] = true;

		//走完需要把走过的点删掉
		for (int k = minIdx; k < cur-1; k++)
		{
			arr[k] = arr[k + 1];
		}
		cur--;

		//测试
		//printf("删之后：\n");
		//for (int i = 0; i < cur; i++) {
		//	printf("%d:(%d,%d)g:%d h:%d f:%d\n", i, arr[i]->p.row, arr[i]->p.col, arr[i]->p.g, arr[i]->p.h, arr[i]->p.f);
		//}

		//判断是否找到终点
		if (curN->p.row == endP.row&&
			curN->p.col == endP.col) {
			isFind = true;
			break;
		}
		//判断数组是否为空
		if (0 == cur) {
			break;
		}

	}//while(true) end

	if (isFind) {
		printf("找到终点了！\n");
		//打印路径
		while (curN)
		{
			printf("(%d,%d)\n", curN->p.row, curN->p.col);
			curN = curN->parent;
		}
	}
	else {
		printf("找不到终点！\n");
	}

	return 0;
}
