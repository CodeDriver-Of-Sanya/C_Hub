#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//特殊标记
#define STATE_DATA 6666
//是都显示特殊标记
#define IS_SHOW 1

/*二叉树
	最多有两个孩子的树
	插入：
		空树->第一个节点进来，判断为空就赋值
		非空树->规定优先往左插入，定义一个特殊标记，遇到特殊标记就不往左，往右插入
	遍历：
		常规的遍历：
			先序遍历：根 左 右
			中序遍历：左 根 右
			后序遍历：左 右 根
			看法：先整体，再局部，再整体，再局部。。。
		已知先序和中序，可以推导出来后序
		已知中序和后序，可以推导出来先序
		已知先序和后序，不能推导出来中序！
	删除：
		1.删根节点
			根节点的右孩子成为新的根节点，左孩子成为 新的根节点 的最左孩子
			若没有右孩子，那么根节点的左孩子成为新的根节点
		2.非根节点
			找到待删节点和它的父节点
			待删节点是它父节点的左孩子：
				待删节点的左孩子成为它右节点的最左孩子
				待删节点的右孩子成为它父节点的左孩子（代替待删节点的位置）
			待删节点是它父节点的右孩子：
				待删节点的左孩子成为它右节点的最左孩子
				待删节点的右孩子成为它父节点的右孩子（代替待删节点的位置）
*/
//树的节点类型
struct Node {
	int data;
	struct Node* pLeft;
	struct Node* pRight;
};

//创建节点
struct Node* createNode(int data) {
	struct Node* pNew = malloc(sizeof(struct Node));
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pLeft = pNew->pRight = NULL;
	return pNew;
}

//插入节点
bool insertNode(struct Node** proot,int insertData) {
	if (proot == NULL)return false;
	if (*proot == NULL) {
		//如果是空树
		*proot = createNode(insertData);
		return true;
	}
	//非空树
	if (STATE_DATA == (*proot)->data)return false;
	//往左子树插入
	if(insertNode(&((*proot)->pLeft), insertData))return true;
	//往右子树插入
	insertNode(&((*proot)->pRight), insertData);
}

//先序遍历
void preTravel(struct Node* proot) {
	if (NULL == proot)return;
	
	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

	//先根
	printf("%4d ", proot->data);
	//再左
	preTravel(proot->pLeft);
	//后右
	preTravel(proot->pRight);
}
//中序遍历
void midTravel(struct Node* proot) {
	if (NULL == proot)return;

	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

	//先左
	midTravel(proot->pLeft);
	//再根
	printf("%4d ", proot->data);
	//后右
	midTravel(proot->pRight);
}
//后序遍历
void lstTravel(struct Node* proot) {
	if (NULL == proot)return;

	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

	//先左
	lstTravel(proot->pLeft);
	//再右
	lstTravel(proot->pRight);
	//后根
	printf("%4d ", proot->data);
}

//遍历
void travel(struct Node* proot, int type) {
	if (type < 0) {
		//先序
		printf("先序遍历：");
		preTravel(proot);
		printf("\n");
	}
	else if (0 == type) {
		//中序
		printf("中序遍历：");
		midTravel(proot);
		printf("\n");
	}
	else {
		//后序
		printf("后序遍历：");
		lstTravel(proot);
		printf("\n");
	}
}

//删除对应数据的节点（不考虑重复）
bool deleteNode(struct Node** pproot, int delData) {
	if (NULL == pproot || NULL == *pproot)return false;
	struct Node* pDel = NULL;
	//1.删根节点
	if (delData == (*pproot)->data) {
		//临时存储根节点的右孩子
		//struct Node* pTempR = (*pproot)->pRight;
		//1.2如果没有右孩子，那就根节点的左孩子成为新的根节点
		if (NULL == (*pproot)->pRight) {
			pDel = *pproot;
			*pproot = (*pproot)->pLeft;
			free(pDel);
			return true;
		}
		else {
			//1.1右孩子成为新的根节点,左孩子成为新的根节点的最左孩子
			struct Node* pTempR = (*pproot)->pRight;
			while (pTempR->pLeft)
			{
				pTempR = pTempR->pLeft;
			}
			pTempR->pLeft = (*pproot)->pLeft;
			pDel = *pproot;
			*pproot = (*pproot)->pRight;
			free(pDel);
			return true;

		}

		
		
		
		
	}
	return false;
}

int main() {
	struct Node* root = NULL;
	int arr[] = { 8,63,STATE_DATA,STATE_DATA ,17,7,44,STATE_DATA ,38,STATE_DATA ,STATE_DATA ,STATE_DATA ,5,STATE_DATA };

	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		insertNode(&root,arr[i]);
	}

	travel(root, -1);
	travel(root, 0);
	travel(root, 1);

	int n;
	while (true)
	{
		printf("请输入要删除的节点：");
		scanf("%d", &n);
		deleteNode(&root, n);
		travel(root, 1);
	}

	while (1);
	return 0;
}
