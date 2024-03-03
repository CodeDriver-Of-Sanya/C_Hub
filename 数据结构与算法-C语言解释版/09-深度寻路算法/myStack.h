#pragma once
#include"res.h"
typedef struct myStack
{
	struct myPoint* pBuff;
	int len;
	int maxlen;
}myStack;

//初始化栈
void init(struct myStack* s);

//入栈
void push(struct myStack* s, struct myPoint* p);

//出栈
void pop(struct myStack* s);

//获取栈顶
struct myPoint* getTop(struct myStack* s);

//判断栈是否为空
bool isEmpty(struct myStack* s);

