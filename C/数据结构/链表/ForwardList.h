#pragma once
typedef struct Node
{
	int data;
	struct Node* next;
}Node,List;

//链表初始化
void flist_init(List* list);

//链表销毁
void flist_clean(List* list);

//尾插
void flist_push(List* list,int val);

//头插
void flist_pop(List* list,int val);

//在中间插入
void flist_insert(List* list, int after, int val);

//链表数据打印
void flist_print(List* list);

//尾删
void flist_tailDel(List* list);

//头删
void flist_popDel(List* list);

//删除指定元素
void flist_distDel(List* list,int val);

//获取链表大小
int flist_size(List* list);

//链表查找
int* flist_find(List* list, int val);

//排序
void flist_sort(List* list);

//链表反转
void flist_reverse(List* list);

