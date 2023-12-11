#pragma once
#include<stdint.h>

//抽象数据类型
typedef int Data;

//节点
typedef struct Node {
	Data data;
	struct Node* next;
}Node;

//链表结构
typedef struct LinkList
{
	//头节点
	Node* front;
	//尾节点
	Node* tail;
	//节点个数
	size_t size;

}LinkList;

/**
 * 创建链表
 * 
 * @return 返回创建成功的链表的指针.
 */

//创建链表
LinkList* CreatLinkList();

//销毁链表
void destoryLinkList(LinkList* list);

//从头部插入数据
void linkList_push_front(LinkList* list, Data val);

//从尾部插入数据
void linkList_push_back(LinkList* list, Data val);

//从指定元素后面插入数据
void linkList_push(LinkList* list, Data after,Data val);

//头删
void linkList_pop_front(LinkList* list);

//尾删
void linkList_pop_back(LinkList* list);

//指定删
void linkList_pop(LinkList* list,Data val);




