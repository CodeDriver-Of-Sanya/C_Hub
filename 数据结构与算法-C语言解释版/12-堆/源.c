#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define NUM 10

/*
满二叉树：
	1.要么没有孩子（叶子节点）要么就有两个孩子，不允许出现有一个孩子的节点
	2.叶子节点在同一层
根节点高度为0，根节点的下一层高度为1，以此类推
高度为m的那一层节点数为 2的m次方
高度为n的满二叉树节点数为 2的n-1次方
完全二叉树：
	从最下面一层，从最右边往左边删除若干节点
	可以用线性结构（数组）描述完全二叉树
		有规律：父节点下标n，其左孩子下标2*n+1,其右孩子下标2*n+2
序列式容器：里面的数据无序
已序式容器：里面的数据有序
堆：
	有序的完全二叉树
		父>子：大顶堆（最大堆）=降序
		父<子：小顶堆（最小堆）=升序

	堆的插入：
		1.按照数组的方式加到最后
		2.临时存储待插数据
		3.往上循环（到根节点或者是不冲突的节点结束）
		4.循环体内 父节点覆盖子节点
		5.循环结束后，用临时存储的待插数据覆盖当前节点
	堆的删除：
		1.临时保存待删数据（堆顶元素）
		2.找左右子树中较小的那个
		3.循环往下归位（两数交换）
			比左右子树中最小的那个都小，循环结束
			越界，循环结束
		4.循环体里 当前节点和左右子树中最小的交换
		5.循环结束后len--
*/

struct Heap {
	int* pRoot;//指向根节点的指针
	int curSize;
	int MaxSize;
};

//初始化
void initHeap(struct Heap* h) {
	h->pRoot = NULL;
	h->curSize = 0;
	h->MaxSize = 0;
}
//插入
void insertNode(struct Heap* h, int inData) {
	//先判断容器是否能插下
	if (h->MaxSize <= h->curSize) {
		h->MaxSize = h->MaxSize + ((h->MaxSize / 2) > 1 ? (h->MaxSize / 2) : 1);
		int* pNew = malloc(h->MaxSize * sizeof(struct Heap));
		if (h->pRoot) {
			memcpy(pNew, h->pRoot, h->curSize * sizeof(struct Heap));
			free(h->pRoot);
		}
		h->pRoot = pNew;
	}
	//先处理特殊情况
	if (0 == h->curSize) {
		h->pRoot[h->curSize++] = inData;
		return;
	}
	//临时存储待插数据
	int tempData = inData;
	//临时存储当先下标（向上循环用）
	int curIdx = h->curSize;
	int parentIdx;

	while (1)
	{
		if (curIdx % 2 == 1) {
			parentIdx = (curIdx - 1) / 2;
		}
		else {
			parentIdx = (curIdx - 2) / 2;
		}
		

		if (curIdx <= 0)break;
		if (h->pRoot[parentIdx] < inData)break;
		//向下覆盖（父节点覆盖子节点）
		h->pRoot[curIdx] = h->pRoot[parentIdx];
		curIdx = parentIdx;
	}
	h->pRoot[curIdx] = inData;
	h->curSize++;
}
//遍历
void travel(struct Heap* h) {
	printf("Heap：\n");
	for (int i = 0; i < h->curSize; i++)
	{
		printf("%2d ", h->pRoot[i]);
	}
	printf("\n");
}
//删除堆顶
int delTop(struct Heap* h) {
	if (NULL == h)return -2;
	if (0 == h->curSize)return -1;
	if (1 == h->curSize) {
		h->curSize = 0;
		return h->pRoot[0];
	}
	//临时保存待删数据
	int temp = h->pRoot[0];
	//当前idx
	int curIdx = 0;
	//左右子树中最小的那个的idx
	int minIdx;

	//最后一个数据覆盖堆顶数据
	h->pRoot[0] = h->pRoot[h->curSize - 1];
	while (1)
	{
		//判断是否越界
		if ((curIdx * 2 + 1) > h->curSize-1 ||
			(curIdx * 2 + 2) > h->curSize-1) {
			break;
		}
		//先假设左子树是最小的
		minIdx = curIdx * 2 + 1;
		//如果左边不是最小的，就换成右边的
		if (h->pRoot[minIdx + 1] < h->pRoot[minIdx]) {
			minIdx++;
		}
		//判断现在在堆顶的数据是否要比minidx还小
		if (h->pRoot[h->curSize - 1] < h->pRoot[minIdx]) {
			break;
		}

		//不小就开始向上覆盖(子覆盖父，不交换了，用覆盖更省资源)
		h->pRoot[curIdx] = h->pRoot[minIdx];
		
		//idx向下走
		curIdx = minIdx;

	}
	//循环结束之后，最后一个数据覆盖当前位置
	h->pRoot[curIdx] = h->pRoot[h->curSize - 1];
	//删除完成
	h->curSize--;
	return temp;
}


int main() {
	int arr[NUM] = { 12,66,39,48,53,72,99,1,9,41 };
	struct Heap h;
	initHeap(&h);

	for (int i = 0; i < NUM; i++)
	{
		insertNode(&h, arr[i]);
		travel(&h);
	}

	for (int i = 0; i < NUM; i++)
	{
		delTop(&h);
		travel(&h);
	}
	

	return 0;
}