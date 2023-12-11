#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<malloc.h>
#include<vector>
using namespace std;

//链表节点类型
struct Node {
	int data;
	struct Node* pNext;
};

//创建链表节点的函数
struct Node* creatNode(int data) {
	struct Node* pNew = new Node;
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pNext = NULL;
	return pNew;
}

//哈希表
struct HashTable {
	vector<vector<vector<Node*>>> arr;
};

//初始化哈希表的函数
void initHash(HashTable* phash) {
	if (NULL == phash)return;
	//第一层
	vector<vector<vector<Node*>>> ptemp1;
	phash->arr = ptemp1;
	//第二层
	for (int i = 0; i < 10; i++)
	{
		vector<vector<Node*>> ptemp2;
		phash->arr.push_back(ptemp2);

		//第三层
		for (int j = 0; j < 10; j++)
		{
			vector<Node*> ptemp3;
			//顺便初始化
			for (int k = 0; k < 10; k++)
			{
				ptemp3.push_back(NULL);
			}
			phash->arr[i].push_back(ptemp3);
		}
	}
}

//释放hash表
void freeHash(HashTable* phash) {
	
}

//往hash表中放数据的函数
void push(HashTable* phash, int data) {
	if (NULL == phash)return;
	Node* pNew = creatNode(data);
	if (NULL == pNew)return;

	//拿到各个位上的数
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	//先拿到对应位置上的指针
	Node* pTemp = phash->arr[bai][shi][ge];

	//看看是否已经有数据
	if (pTemp) {
		//尾插
		while (pTemp->pNext)pTemp = pTemp->pNext;
		pTemp->pNext = pNew;
	}
	else {
		phash->arr[bai][shi][ge] = pNew;
	}
}

//查找hash表中数据的函数
Node* find(HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	//拿到各个位上的数
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	Node* pTemp = phash->arr[bai][shi][ge];
	while (pTemp) {
		if (data == pTemp->data)return pTemp;
		pTemp = pTemp->pNext;
	}
	return NULL;

}

int main() {
	struct HashTable h;
	initHash(&h);

	int n;
	int data;
	bool isEnd = true;
	struct Node* pTemp;
	while (isEnd)
	{
		printf("1 - 插入\n");
		printf("2 - 查找\n");
		printf("3 - 退出\n");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("请输入要插入的数据 > ");
			scanf("%d", &data);
			push(&h, data);
			printf("插入完毕！\n");
			break;
		case 2:
			printf("请输入要查找的数据 > ");
			scanf("%d", &data);
			pTemp = find(&h, data);
			if (NULL == pTemp) {
				printf("没有找到！\n");
			}
			else {
				printf("找到了：%d\n", pTemp->data);
			}
			break;
		case 3:
			freeHash(&h);
			isEnd = false;
			break;
		default:
			printf("无此选项！\n");
			break;
		}
	}

	return 0;
}


/*

if (NULL == phash)return;
	//释放最下层
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			free(phash->arr[i][j]);
		}
	}
	//释放第二层
	for (int i = 0; i < 10; i++)
	{
		free(phash->arr[i]);
	}
	//释放第一层
	free(phash->arr);
*/





