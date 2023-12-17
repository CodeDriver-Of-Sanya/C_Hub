#include "List.h"

bool isValid(List* list) 
{
	if (list == NULL)
	{
		printf("list invalid!\n");
		return false;
	}
	return true;
}

Node* createNode(variant _data)
{
	Node* newNode = calloc(1,sizeof(Node));
	if (!newNode) 
	{
		printf("newNode calloc failed!\n");
		return NULL;
	}

	newNode->data = _data;
	return newNode;
}

void list_init(List* list)
{
	if (!isValid(list)) return;

	list->phead = list->ptail = calloc(1, sizeof(Node));
	if (list->phead == NULL)
	{
		printf("phead and ptail calloc failed!\n");
		return;
	}

	list->size = 0;
}

void list_pushBack(List* list, variant _data)
{
	if (!isValid(list)) return;

	Node* newNode = calloc(1, sizeof(Node));
	newNode->data = _data;
	list->ptail->pnext = newNode;
	list->ptail = newNode;
	list->size++;
}

void list_removeOne(List* list, variant _data)
{
	if (!isValid(list)) return;

	//找删除节点
	Node* curNode = list->phead->pnext;
	Node* prevNode = list->phead;
	while (curNode) 
	{
		if (curNode->pnext->data == _data) {
			break;
		}
		prevNode = curNode;
		curNode = curNode->pnext;
	}

	//进行节点删除
	if (curNode) 
	{
		prevNode->pnext = curNode->pnext;
		free(curNode);
	}

}

void list_transfrom(List* list, LISTCALLBACK callBack)
{
	if (!isValid(list)) return;
	//遍历链表，调用callback函数
	Node* curNode = list->phead->pnext;
	while (curNode)
	{
		callBack(curNode->data);
		curNode = curNode->pnext;
	}
}

variant list_search(List* list, CMPCALLBACK cmp, variant _data)
{
	Node* curNode = list->phead->pnext;
	while (curNode)
	{
		if (cmp(curNode->data, _data)) {
			return curNode->data;
		}
		curNode = curNode->pnext;
	}
	return NULL;
}

void list_destory(List* list)
{
	if (!isValid(list)) return;

	Node* curNode = list->phead;
	Node* delNode;
	while (curNode)
	{
		delNode = curNode;
		curNode = curNode->pnext;
		free(delNode);
	}
}
