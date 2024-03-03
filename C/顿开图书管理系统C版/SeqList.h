#ifndef _SEQLIST_H_
#define _SEQLIST_H_
#include "Configure.h"
#define SEQLIST_INIT_SIZE 10

typedef struct SeqList {
	int size;//元素个数
	int capacity;//表容量
	variant* pparr;//指向 指针数组 的指针
}SeqList;

//宏顺序表

//初始化顺序表
#define SeqList_init(plist)\
(plist)->size = 0;\
(plist)->capacity = SEQLIST_INIT_SIZE;\
(plist)->pparr = calloc((plist)->capacity,sizeof(variant));\
if(!(plist)->pparr)\
{\
	printf("pparr calloc failed!\n");\
}

//尾插元素
#define SeqList_pushBack(plist,val)\
if((plist)->size>=(plist)->capacity)\
{\
	(plist)->capacity *= 2;\
	(plist)->pparr=realloc((plist)->pparr, (plist)->capacity * sizeof(variant));\
}\
(plist)->pparr[(plist)->size++]=val;

//遍历
#define foreach(variable,plist)\
for (int _i = 0,_j=0; _i < (plist)->size; _i++,_j=0)\
	for(variable=(plist)->pparr[_i];_j<1;_j++)


#endif // !_SEQLIST_H_
