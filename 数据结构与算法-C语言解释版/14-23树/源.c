#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

/*
* 23树：
相对于平衡二叉树，插入删除效率更高
二节点：一个数据，两个指针
三节点：两个数据，三个指针
四节点（临时存在）：三个数据，四个指针
*/

enum types {
	null_node,
	two_node,
	three_node,
	four_node
};

//节点类型
struct treeNode {
	//标记是2节点（1）还是3节点（2）还是4节点（3）
	int cnt;
	//数据
	int data[3];
	//指针
	struct treeNode* pArr[4];
};

//创建节点函数
struct treeNode* createNode() {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	return pNew;
}

//插入节点到树中
void insertNode(struct treeNode** pRoot, int inData) {
	if (NULL == pRoot)return;
	if (NULL == *pRoot) {
		//空树
		*pRoot = createNode();
		(*pRoot)->cnt = two_node;
		(*pRoot)->data[0] = inData;
	}
	else {
		//如果不是空树
		inNode(*pRoot, NULL, inData);
	}
}
//实际的插入函数
void inNode(struct treeNode* node, struct treeNode* parent, int inData) {
	if (NULL == node)return;
	if (null_node == node->cnt) {
		node->data[0] = inData;
		node->cnt++;
		return;
	}
	if (two_node == node->cnt) {
		if (inData > node->data[0]) {//往右边放
			//判断有没有孩子，有孩子的话需要插到孩子上
			if (node->pArr[1]) {//有孩子
				inNode(node->pArr[1], node, inData);
			}
			else {
				node->data[1] = inData;
				node->cnt++;//变成三节点
			}
			
		}
		else {//往左边放
			//判断有没有孩子，有孩子的话需要插到孩子上
			if (node->pArr[0]) {//有孩子
				inNode(node->pArr[0], node, inData);
			}
			else {
				//先将旧数据往后挪动
				node->data[1] = node->data[0];
				//再将新节点放到第一个
				node->data[0] = inData;
				node->cnt++;
			}
		}
	}
	if (three_node == node->cnt) {
		if (inData<node->data[0]) {//往左插入
			if (node->pArr[0]) {//有孩子
				inNode(node->pArr[0], node, inData);
			}
			else {//没有孩子
				//将前两个数往后挪动
				node->data[2] = node->data[1];
				node->data[1] = node->data[0];
				//新数据进来
				node->data[0] = inData;
				//变成四节点
				node->cnt++;
			}
		}
		else if (inData<node->data[1]) {//往中间插入
			if (node->pArr[1]) {//有孩子
				inNode(node->pArr[1], node, inData);
			}
			else {//没有孩子
				node->data[2] = node->data[1];
				//新数据进来
				node->data[1] = inData;
				//变成四节点
				node->cnt++;
			}
		}
		else {//往右插入
			if (node->pArr[2]) {//有孩子
				inNode(node->pArr[2], node, inData);
			}
			else {//没有孩子
				node->data[2] = inData;
				//变成四节点
				node->cnt++;
			}
		}
	}
	//判断一下是否产生了四节点
	if (four_node == node->cnt) {
		//创建两个新节点
		struct treeNode* nodeL = createNode();
		struct treeNode* nodeR = createNode();
		//新节点赋值
		//左
		nodeL->cnt = two_node;
		nodeL->data[0] = node->data[0];
		nodeL->pArr[0] = node->pArr[0];
		nodeL->pArr[1] = node->pArr[1];
		//右
		nodeR->cnt = two_node;
		nodeR->data[0] = node->data[2];
		nodeR->pArr[0] = node->pArr[2];
		nodeR->pArr[1] = node->pArr[3];

		//临时存储中间值
		int temp = node->data[1];
		//若有父节点，对父节点作插入
		if (parent) {
			//
			if (temp < parent->data[0]) {//往左做插入
				if (parent->pArr[2]) {//最右边有孩子
					parent->data[2] = parent->data[1];
					parent->data[1] = parent->data[0];
					parent->data[0] = temp;

					parent->pArr[3] = parent->pArr[2];
					parent->pArr[2] = parent->pArr[1];
					parent->pArr[1] = nodeR;
					parent->pArr[0] = nodeL;

				}
				else if (parent->pArr[1]) {//中间有孩子
					parent->data[1] = parent->data[0];
					parent->data[0] = temp;

					parent->pArr[2] = parent->pArr[1];
					parent->pArr[1] = nodeR;
					parent->pArr[0] = nodeL;
				}
			}
			else if ((two_node == parent->cnt) ||(parent->cnt>1)&& temp < parent->data[1]) {//往中间插入

				if (parent->pArr[2]) {//最右边有孩子
					parent->data[2] = parent->data[1];
					parent->data[1] = temp;

					parent->pArr[3] = parent->pArr[2];
					parent->pArr[2] = nodeR;
					parent->pArr[1] = nodeL;

				}
				else if (parent->pArr[1]) {//中间有孩子
					parent->data[1] = temp;

					parent->pArr[2] = nodeR;
					parent->pArr[1] = nodeL;
				}

			}
			else if ((three_node == parent->cnt) || (parent->cnt > 2) && temp < parent->data[2]) {//往右边插入
				parent->data[2] = temp;

				parent->pArr[3] = nodeR;
				parent->pArr[2] = nodeL;
			}

			//父节点变化
			parent->cnt++;
			//当前节点释放
			free(node);

		}
		else {//若没有父节点，当前节点变化

			//先清空节点
			memset(node->data, 0, sizeof(int) * 3);
			memset(node->pArr, 0, sizeof(struct treeNode) * 4);

			//当前节点变成二节点
			node->cnt = two_node;
			//数据变化
			node->data[0] = temp;
			//指针变化
			node->pArr[0] = nodeL;
			node->pArr[1] = nodeR;

		}
		
	}
}

int main() {

	int arr[] = { 38,66,56,39,41,58,18,8,99,78,33,76,36,45,92,3 };
	int len = 16;

	struct treeNode* root = NULL;

	for (int i = 0; i < len; i++)
	{
		insertNode(&root, arr[i]);
	}

	return 0;
}
