#include "ForwardList.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdbool.h>

static Node* CreateNode(int val) {
	Node* newNode = calloc(1, sizeof(Node));
	if (!newNode) {
		return;
	}
	newNode->data = val;
	return newNode;
}

void flist_init(List* list) {
	if (!list)return;

	memset(list, 0, sizeof(Node));
	list->data = 0;
}

void flist_clean(List* list)
{
	//释放所有数据节点
	Node* curNode = list->next;
	Node* delNode = NULL;

	while (curNode)
	{
		delNode = curNode;
		curNode = curNode->next;
		free(delNode);
	}
}

void flist_push(List* list, int val)
{
	//找到最后一个元素节点
	Node* curNode = list;
	while (curNode->next) {
		curNode = curNode->next;
	}

	Node* newNode = CreateNode(val);
	curNode->next = newNode;
	list->data++;
}

void flist_pop(List* list, int val)
{
	Node* newNode = CreateNode(val);
	newNode->next = list->next;
	list->next = newNode;
	list->data++;
}

void flist_insert(List* list, int after, int val)
{
	if (list->next == NULL) {
		perror("空链表无法进行插入操作！");
		return;
	}
	Node* curNode = list;
	while (curNode->data!=after)
	{
		curNode = curNode->next;
	}
	Node* newNode = CreateNode(val);
	newNode->next = curNode->next;
	curNode->next = newNode;
	list->data++;
}

void flist_print(List* list)
{
	Node* curNode = list->next;
	printf("===============\n");
	while (curNode) {
		printf("%d\n", curNode->data);
		curNode = curNode->next;
	}
	printf("===============\n");
}

void flist_tailDel(List* list)
{
	if (list->next == NULL) {
		perror("空链表无法进行尾删操作！");
		return;
	}
	Node* curNode = list;
	Node* prevNode = NULL;
	while (curNode->next)
	{
		prevNode = curNode;
		curNode = curNode->next;
	}

	free(curNode);
	prevNode->next = NULL;
	list->data--;
}

void flist_popDel(List* list)
{
	if (list->next == NULL) {
		perror("空链表无法进行头删操作！");
		return;
	}
	Node* curNode = list->next;
	list->next = curNode->next;
	free(curNode);
	list->data--;
}

void flist_distDel(List* list,int val)
{
	if (list->next == NULL) {
		perror("空链表无法进行指定元素删除操作！");
		return;
	}

	Node* curNode = list;
	Node* delNode = NULL;
	while (curNode->next->data!=val)
	{
		curNode = curNode->next;
	}
	delNode = curNode->next;
	curNode->next = delNode->next;
	free(delNode);
	list->data--;

}

int flist_size(List* list)
{
	Node* curNode = list->next;
	int cnt = 0;
	while (curNode)
	{
		cnt++;
		curNode = curNode->next;
	}
	return cnt;
}

int* flist_find(List* list, int val)
{
	Node* curNode = list->next;
	while (curNode) {
		if (curNode->data == val) {
			return &curNode->data;
		}
		curNode = curNode->next;
	}
	return NULL;
}

void flist_sort(List* list)
{
	if (list->next == NULL) {
		perror("空链表无法进行排序操作！");
		return;
	}
	for (Node* i = list->next; i !=NULL ; i=i->next)
	{
		bool isSort = true;
		for (Node* curNode = list->next; curNode->next != NULL; curNode = curNode->next) {
			if (curNode->data > curNode->next->data) {
				int temp = curNode->data;
				curNode->data = curNode->next->data;
				curNode->next->data = temp;
				isSort = false;
			}
		}
		if (isSort)
			break;
	}
}

void flist_reverse(List* list)
{
	if (list->next == NULL) {
		perror("空链表无法进行反转操作！");
		return;
	}
	Node* curNode = list->next;
	Node* nextNode = NULL;
	Node* prevNode = NULL;
	while (curNode)
	{
		nextNode = curNode->next;
		curNode->next = prevNode;
		prevNode = curNode;
		curNode = nextNode;
	}
	list->next = prevNode;

}
