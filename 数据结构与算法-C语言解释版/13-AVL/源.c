#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*
平衡二叉树（AVL）：
如果根节点左子树节点数量太多或者太少，搜索效率就不高
	所以要左右两边节点数量差不多
	即：左右子树高度差不超过1的有序二叉树
		高度：距离根节点的节点数量（路径长度，或者说层数）
如何构建：
	1.先按有序二叉树的方式插入
	2.插入后检查是否平衡
		如果平衡，不用管
		如果插入后不平衡，通过旋转让他平衡
不平衡的四种情况（是局部的情况，不是整体的）：
1.					o(根节点)
				o(当前节点)
			o(新节点)
以根节点为轴右旋：
					o18								o16
				o16				变成			o7		o18
			o7

	1.临时存储根节点的左孩子pTemp
	2.让pTemp的右孩子成为根节点的左孩子
	3.根节点成为pTemp的右孩子
	4.设置下高度
	5.返回pTemp成为新的pRoot


2.					o
						o
							o
以根节点为轴左旋：
					o1										o3
						o3				变成			o1		o5
							o5



3.					o
				o
				   o

左右旋：
先以当前节点为轴左旋，再以根节点为轴右旋
					o10							o10									o6
				o5				先变成		o6					再变成			o5		o10
					o6					o5
	
	1.

4.
					o
						o
					 o
右左旋：
先以当前节点为轴右旋，再以根节点为轴左旋
					o10								o10									o12
						o18			先变成				o12				再变成		o10		o18
					 o12									o18

*/

//平衡二叉树节点类型
struct treeNode {
	int data;
	struct treeNode* pL;
	struct treeNode* pR;
	int height;//注意高度
};

//创建节点函数
struct treeNode* createNode(int data) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew) {
		printf("创建节点失败！");
		return NULL;
	}

	pNew->data = data;
	pNew->pL = NULL;
	pNew->pR = NULL;
	pNew->height = 0;

	return pNew;
}

//获取某个节点的高度
int getHeight(struct treeNode* pRoot) {
	if (NULL == pRoot)return 0;
	return pRoot->height;
}

//情况1-右旋
struct treeNode* RR(struct treeNode* pRoot) {
	struct treeNode* pTemp = pRoot->pL;
	pRoot->pL = pTemp->pR;
	pTemp->pR = pRoot;

	//设置高度
	int LHeight = getHeight(pRoot->pL);
	int RHeight = getHeight(pRoot->pR);
	pRoot->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	LHeight = getHeight(pTemp->pL);
	RHeight = getHeight(pTemp->pR);
	pTemp->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	return pTemp;

}
//情况2-左旋
struct treeNode* LL(struct treeNode* pRoot) {
	struct treeNode* pTemp = pRoot->pR;
	pRoot->pR = pTemp->pL;
	pTemp->pL = pRoot;

	//设置高度
	int LHeight = getHeight(pRoot->pL);
	int RHeight = getHeight(pRoot->pR);
	pRoot->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	LHeight = getHeight(pTemp->pL);
	RHeight = getHeight(pTemp->pR);
	pTemp->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	return pTemp;
}

//情况3-左右旋
struct treeNode* LR(struct treeNode* pRoot) {
	//先以pRoot的左孩子为轴左旋
	pRoot->pL = LL(pRoot->pL);
	//再以pRoot为轴右旋
	return RR(pRoot);
}
//情况4-右左旋
struct treeNode* RL(struct treeNode* pRoot) {
	//先以pRoot的右孩子为轴右旋
	pRoot->pR = RR(pRoot->pR);
	//再以pRoot为轴左旋
	return LL(pRoot);
}

//插入节点
void insertNode(struct treeNode** pRoot, int inData) {
	if (NULL == pRoot)return;
	//最开始先以有序二叉树的方式插入
	if (NULL == *pRoot) {
		*pRoot = createNode(inData);
	}
	else if (inData < (*pRoot)->data) {
		//往左插入
		insertNode(&((*pRoot)->pL), inData);
		//插入完成后检查高度（注意，往左插入，只有左边高度大于右边的可能没有右边大于左边的可能）
		if (getHeight((*pRoot)->pL) - getHeight((*pRoot)->pR) > 1) {
			//不平衡 情况1或者情况3
			if (inData < (*pRoot)->pL->data) {
				//情况1-右旋
				*pRoot = RR((*pRoot));
			}
			else {
				//情况3-左右旋
				*pRoot = LR((*pRoot));
			}
		}
	}
	else {
		//往右插入
		insertNode(&((*pRoot)->pR), inData);
		if (getHeight((*pRoot)->pR) - getHeight((*pRoot)->pL) > 1) {
			//不平衡 情况2或者情况4
			if (inData < (*pRoot)->pR->data) {
				//情况4-右左旋
				*pRoot = RL((*pRoot));
			}
			else {
				//情况2-左旋
				*pRoot = LL((*pRoot));
			}
		}
	}

	//设置高度
	int LHeight = getHeight((*pRoot)->pL);
	int RHeight = getHeight((*pRoot)->pR);
	(*pRoot)->height = 1 + (LHeight > RHeight ? LHeight : RHeight);
}

//先序遍历
void preTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//先根
	printf("%4d ", proot->data);
	//再左
	preTravel(proot->pL);
	//后右
	preTravel(proot->pR);
}
//中序遍历
void midTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//先左
	midTravel(proot->pL);
	//再根
	printf("%4d(%d) ", proot->data,proot->height);
	//后右
	midTravel(proot->pR);
}
//后序遍历
void lstTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//先左
	lstTravel(proot->pL);
	//再右
	lstTravel(proot->pR);
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
		printf("中序遍历(括号中为高度)：");
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

int main() {
	int arr[] = {38,66,56,39,41,58,18,8,99,78,33,76,36,45,92,3};
	int len = 16;

	struct treeNode* root = NULL;

	for (int i = 0; i < len; i++)
	{
		insertNode(&root, arr[i]);
		travel(root, 0);
	}

	while (1);
	return 0;
}
