#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#define NUM 11

void travel(int arr[NUM], int len, bool isAfter) {
	if (isAfter) {
		printf("after sort:");
	}
	else {
		printf("before sort:");
	}

	for (int i = 0; i < len; i++)
	{
		printf("%02d ", arr[i]);
	}

	printf("\n");
}

/*归并排序
	用于两个有序数组合并成一个有序数组
	无序数组用归并排序去排（仅练习使用，一般不要用归并排无序数组，效率太低）：
*/

//两个有序数组合并成一个有序数组
void MergeSort(int arr[NUM], int l, int m, int r) {
	int left = l;
	int right = m + 1;
	int len = r - l + 1;
	int* pTemp = (int*)malloc(sizeof(int) * len);
	int k = 0;
	while (left <= m && right <= r) {
		if (arr[left] < arr[right]) {
			pTemp[k++] = arr[left++];
		}
		else {
			pTemp[k++] = arr[right++];
		}
	}
	//把某一边剩下的放入
	while (left <= m) {
		pTemp[k++] = arr[left++];
	}
	while (right <= r) {
		pTemp[k++] = arr[right++];
	}
	//用临时内存覆盖数组
	k = 0;
	for (int i = l; i < r; i++) {
		arr[i] = pTemp[k++];
	}
	//释放临时内存
	free(pTemp);
}

void mergeSort(int arr[NUM], int left, int right) {
	if (left < right) {
		//拆
		int m = left + (right - left) / 2;
		mergeSort(arr, left, m);//左边
		mergeSort(arr, m + 1, right);//右边
		//合并
		MergeSort(arr, left, m, right);
		printf("left:%d  m:%d  right:%d\n", left, m, right);
		travel(arr+left, right - left + 1, false);
	}
}

void merge_sort(int arr[NUM], int len) {
	mergeSort(arr, 0, len - 1);
}

/*树结构
	现实的树木是从下往上长：下面是根，上面是枝干，再上面是树枝，树叶
	程序员画树：从上往下画
		上面是树根		根节点
		中间是枝干		枝干节点
		下面是树叶		叶子节点

		树结构天然具备递归特性
		树中的节点，也可以看作单独的一棵树 - 子树
		叉：
			一个子		链表，单叉树
			两个子		二叉树
			三个子		三叉树
			以此类推...
			以某一节点分叉最多的定义为整个叉树
				比如有四个节点的树其中有一个有最多的三个子节点，那么称其为三叉树
*/
/*三个指针描述一棵树
	插入：
		插入成为某个节点的孩子或者兄弟
			成为孩子：
				1.无孩子，成为孩子
				2.有孩子，成为最小的孩子
			成为兄弟:
				1.无兄弟，成为兄弟
				2.有兄弟，成为最小的兄弟
*/

struct treeNode
{
	//数据域
	int data;
	//指针域
	struct treeNode* pParent;//父节点
	struct treeNode* pBrother;//兄弟节点
	struct treeNode* pChild;//子节点
};

//创建节点函数
struct treeNode* createNode(int data) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->data = data;
	return pNew;
}

//查找节点函数(找到返回目标节点的指针，没找到返回NULL)
struct treeNode* findNode(struct treeNode* ptree,int findData) {
	if (NULL == ptree)return NULL;
	//先看是否为当前节点
	struct treeNode* pCurrent = ptree;
	
	//然后循环找孩子
	while (pCurrent) {
		//循环找兄弟
		struct treeNode* pBrother = pCurrent;
		while (pBrother) {
			//循环找兄弟的孩子
			struct treeNode* pChild = pBrother;
			while (pChild)
			{
				if (findData == pChild->data) {
					return pChild;
				}
				//下一个孩子
				pChild = pChild->pChild;
			}
			
			//下一个兄弟
			pBrother = pBrother->pBrother;
		}
		//下一个兄弟
		pCurrent = pCurrent->pChild;
	}
	//循环结束还没有，那就没有了
	return NULL;
}

//插入节点函数
//可能需要改动树，所以传树的二级指针，用bool值控制插入为子节点还是兄弟节点
void insertNode(struct treeNode** ptree,int findData, int insertData, bool isChild) {
	if (NULL == ptree)return;
	struct treeNode* pNew = createNode(insertData);
	if (NULL==*ptree) {
		//空树
		*ptree = pNew;
		return;
	}
	struct treeNode* found = findNode(*ptree, findData);
	//没找到
	if (NULL == found) {
		printf("没找到对应节点\n");
		return NULL;
	}
	//找到了
	if (isChild) {
		//成为孩子
		if (found->pChild) {
			//有孩子
			while (found->pChild)
			{
				found = found->pChild;
			}
			found->pChild = pNew;
			pNew->pParent = found;
		}
		else {
			//没有孩子
			found->pChild = pNew;
			pNew->pParent = found;
		}
	}
	else {
		//成为兄弟
		if (found->pBrother) {
			//有兄弟
			while (found->pBrother) {
				found = found->pBrother;
			}
			found->pBrother = pNew;
			pNew->pParent = found->pParent;
		}
		else {
			//无兄弟
			found->pBrother = pNew;
			pNew->pParent = found->pParent;
			return;
		}
	}
}

int main() {
	/*
	int arr[NUM] = { 12,39,48,53,66,1,9,41,72,99,666 };
	travel(arr, NUM, false);

	printf("归并排序：\n");
	merge_sort(arr, NUM);

	travel(arr, NUM, true);
	*/
	//树	树的根节点
	struct treeNode* pRoot = NULL;

	insertNode(&pRoot, 10, 1, true);
	insertNode(&pRoot, 1, 2, true);
	insertNode(&pRoot, 1, 3, true);
	insertNode(&pRoot, 2, 22, false);
	insertNode(&pRoot, 2, 24, false);
	insertNode(&pRoot, 24, 333, true);
	insertNode(&pRoot, 24, 444, true);


	while (1);
	return 0;
}
