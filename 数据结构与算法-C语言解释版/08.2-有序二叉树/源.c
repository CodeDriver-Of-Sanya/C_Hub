#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

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
bool insertNode(struct Node** proot, int insertData) {
	if (proot == NULL)return false;
	if (*proot == NULL) {
		//如果是空树
		*proot = createNode(insertData);
		return true;
	}
	//往左子树插入
	if (insertData < (*proot)->data) {
		return insertNode(&((*proot)->pLeft), insertData);
	}
	//往右子树插入
	if (insertData > (*proot)->data) {
		return insertNode(&((*proot)->pRight), insertData);
	}
}

//先序遍历
void preTravel(struct Node* proot) {
	if (NULL == proot)return;

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

//查找节点
struct Node* findNode(struct Node* proot,int findData){
	if (NULL == proot)return NULL;
	while (proot) {
		if (findData == proot->data)return proot;
		if (findData < proot->data) {
			proot = proot->pLeft;
		}
		else {
			proot = proot->pRight;
		}
	}

	return NULL;
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
			pDel = NULL;
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
			pDel = NULL;
			return true;

		}
	}

	//2.删除非根节点
	pDel = findNode(*pproot, delData);
	if (NULL == pDel) return false;
	struct Node* pTemp = *pproot;
	struct Node* pDelParent = NULL;

	//找删除节点的父节点
	while (1) {
		pDel = pTemp;
		if (delData == pTemp->data)break;
		pDelParent = pTemp;
		if (delData < pTemp->data) {
			pTemp = pTemp->pLeft;
		}
		else {
			pTemp = pTemp->pRight;
		}
	}
	if (pDel == pDelParent->pLeft) {
		//要删节点是其父节点的左孩子
		if (NULL == pDel->pRight) {
			//要删节点没有右孩子,直接让其左孩子成为父节点的左孩子
			pDelParent->pLeft = pDel->pLeft;
			free(pDel);
			return true;
		}
		pTemp = pDel->pRight;
		while (pTemp->pLeft)
		{
			pTemp = pTemp->pLeft;
		}
		//1.pdel的左孩子成为pdel右孩子的最左孩子
		pTemp->pLeft = pDel->pLeft;
		//2.pdel的右孩子成为父节点的左孩子
		pDelParent->pLeft = pDel->pRight;

		free(pDel);
		pDel = NULL;
		return true;
	}
	else {
		//要删节点是其父节点右左孩子
		//同理
		if (NULL == pDel->pRight) {
			pDelParent->pRight = pDel->pLeft;
			free(pDel);
			return true;
		}
		pTemp = pDel->pRight;
		while (pTemp && pTemp->pLeft)
		{
			pTemp = pTemp->pLeft;
		}
		pTemp->pLeft = pDel->pLeft;
		pDelParent->pRight = pDel->pRight;
		free(pDel);
		pDel = NULL;
		return true;
	}

	return false;
}

int main() {
	struct Node* root = NULL;

	int arr[] = { 7,1,9,8,6,5,2,44,38,96,57,66,83 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		insertNode(&root, arr[i]);
	}
	travel(root, 0);

	int n;
	while (true)
	{
		printf("请输入要删除的节点：");
		scanf("%d", &n);
		deleteNode(&root, n);
		travel(root, 0);
		printf("\n");
	}

	while (1);
	return 0;
}