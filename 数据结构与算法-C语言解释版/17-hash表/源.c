#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*
* 07
* 
hash表（哈希表/散列表/散列法）

作为数据结构而言：查找效率非常高

作为算法而言：加密算法

哈希三要素：
1.数据的范围
	确定了数据的管理方式 范围也就明确了
2.合适的hash函数
	返回数据的地址的函数，找数据的方式
3.解决冲突的办法
	健壮性考虑，解决冗余：hash表看起来是一样的数据，要有办法区分

假设构建一个hash表来存 1000以内 的整数

十进制整数 每个位上的数据 0-9

*/

//解决冲突 用链表

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
	struct Node* arr[10][10][10];
};

//初始化哈希表的函数
void initHash(struct HashTable* phash) {
	if (NULL == phash)return;
	memset(phash->arr, 0, sizeof(phash->arr));
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
	while (true)
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
				printf("找到了：%d\n",pTemp->data);
			}
			break;
		case 3:
			return 0;
			break;
		default:
			printf("无此选项！\n");
			break;
		}
	}

	while (1);
	return 0;
}
