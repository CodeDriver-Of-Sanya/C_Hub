#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<malloc.h>

//链表节点类型
struct Node {
	int data;
	struct Node* pNext;
};

//创建链表节点的函数
struct Node* creatNode(int data) {
	struct Node* pNew = malloc(sizeof(struct Node));
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pNext = NULL;
	return pNew;
}

//哈希表
struct HashTable {
	struct Node**** arr;
};

//初始化哈希表的函数
void initHash(struct HashTable* phash) {
	if (NULL == phash)return;

	//第一层
	phash->arr = malloc(10 * sizeof(struct Node***));
	//第二层
	for (int i = 0; i < 10; i++)
	{
		phash->arr[i]= malloc(10 * sizeof(struct Node**));
	}
	//第三层
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			phash->arr[i][j] = malloc(10 * sizeof(struct Node*));

			//初始化
			memset(phash->arr[i][j], 0, 10 * sizeof(struct Node*));
		}
	}
}
//释放hash表
void freeHash(struct HashTable* phash) {
	if (NULL == phash)return;
	if (NULL == phash->arr)return;
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
}

//往hash表中放数据的函数
void push(struct HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	struct Node* pNew = creatNode(data);
	if (NULL == pNew)return NULL;

	//拿到各个位上的数
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	//先拿到对应位置上的指针
	struct Node* pTemp = phash->arr[bai][shi][ge];

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
struct Node* find(struct HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	//拿到各个位上的数
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	struct Node* pTemp = phash->arr[bai][shi][ge];
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
			struct Node* pTemp = find(&h, data);
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
