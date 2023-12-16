#ifndef _LIST_H_
#define _LIST_H_
#include"Configure.h"
//链表

typedef struct Node 
{
	variant data;//指向数据的指针
	struct Node* pnext;//指向下一个节点的指针
}Node;

//封装链表
typedef struct List 
{
	int size;//有效元素个数
	Node* phead;
	Node* ptail;
}List;

//回调函数类型
typedef void(*LISTCALLBACK)(variant);

//创建节点
Node* createNode(variant _data);

//初始化链表
void list_init(List* list);

//插入元素
void list_pushBack(List* list, variant _data);

//删除元素
void list_removeOne(List* list, variant _data);

//使用回调函数处理每个数据
void list_transfrom(List* list, LISTCALLBACK callBack);

//查找元素
typedef bool (*CMPCALLBACK)(variant, variant);
variant list_search(List* list, CMPCALLBACK cmp, variant _data);

//销毁链表
void list_destory(List* list);

#endif // !_LIST_H
