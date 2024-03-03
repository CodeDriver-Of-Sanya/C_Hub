#include "LinkList.h"
#include <malloc.h>
#include<stdio.h>


static Node* CreateNode(Data val) {
	Node* newNode=(Node*)calloc(1,sizeof(Node));
	if (!newNode) {
		return NULL;
	}
	newNode->data = val;
}

LinkList* CreatLinkList()
{
	LinkList* list = calloc(1, sizeof(LinkList));
	if (!list) {
		return NULL;
	}
	//申请头节点和尾节点
	list->front = list->tail=calloc(1,sizeof(Node));
	if (!list->front) {
		free(list);
		return NULL;
	}
	return list;
}

void destoryLinkList(LinkList* list)
{
	if (!list)
		return;
	Node* curNode = list->front;
	Node* delNode = NULL;

	while (curNode)
	{
		delNode = curNode;
		curNode = curNode->next;
		free(delNode);
	}
	free(list);
}

void linkList_push_front(LinkList* list, Data val)
{
	Node* newNode = CreateNode(val);
	newNode->next = list->front;
	list->front = newNode;
	if (list->size == 0) {
		list->tail = newNode;
	}
	list->size++;
}

void linkList_push_back(LinkList* list, Data val)
{
	Node* newNode = CreateNode(val);
	list->tail->next = newNode;
	list->tail = newNode;
	if (list->size == 0) {
		list->front = newNode;
	}
	list->size++;
}

void linkList_push(LinkList* list, Data after, Data val)
{
	if (!list) {
		printf("空链表，无法指定插入！");
		return;
	}

	Node* curNode = list->front;
	while (curNode)
	{
		if (curNode->data == after) {
			Node* newNode = CreateNode(val);

			newNode->next = curNode->next;
			//判断curNode是不是最后一个节点
			if (curNode->next == NULL) {
				list->tail = newNode;
			}
			curNode->next = newNode;
			
			list->size++;
			break;
		}
		curNode = curNode->next;
	}

}

void linkList_pop_front(LinkList* list)
{
	if (list->size == 0) { 
		printf("空链表不能删除元素！");
		return;
	}

	Node* delNode = list->front;
	if (list->size == 1) {
		list->front = list->tail = CreateNode(0);
		free(delNode);
		list->size--;
		return;
	}
	list->front = list->front->next;
	free(delNode);
	list->size--;
}

void linkList_pop_back(LinkList* list)
{
	if (list->size == 0) {
		printf("空链表不能删除元素！");
		return;
	}

	Node* curNode = list->front;
	Node* delNode = list->tail;

	if (list->size == 1) {
		list->front = list->tail = CreateNode(0);
		free(delNode);
		list->size--;
		return;
	}
	while (curNode->next!=list->tail)
	{
		curNode = curNode->next;
	}
	
	free(delNode);
	list->tail = curNode;
	list->tail->next = NULL;
	list->size--;

}
