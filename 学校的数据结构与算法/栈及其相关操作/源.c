#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>

struct myStack {
	int* parr;
	int headIdx;
	int tailIdx;
	int capacity;
};

//初始化
void myStackInit(struct myStack* s) {
	s->capacity = 10;
	s->parr = calloc(s->capacity, sizeof(int));
	s->headIdx = s->tailIdx = 0;
}

//是否栈空
bool isEmpty(struct myStack* s) {
	if (NULL == s) {
		return true;
	}
	if (s->headIdx == s->tailIdx) {
		return true;
	}
	else {
		return false;
	}
}

//栈中元素个数
int myStackSize(struct myStack* s) {
	return s->tailIdx;
}

//入栈
void push(struct myStack* s, int data) {
	if (NULL == s)return;
	if (s->tailIdx >= s->capacity) {
		printf("栈满，无法插入！\n");
		return;
	}
	s->parr[s->tailIdx++] = data;
	printf("插入成功\n");
}

//出栈
void pop(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("栈空，无法删除！\n");
		return;
	}
	s->tailIdx--;
}

//遍历栈
void travel(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("栈空！\n");
		return;
	}
	for (int i = 0; i < s->tailIdx; i++)
	{
		printf("%d ", s->parr[i]);
	}
	printf("\n");
}

//返回栈顶元素数据
int myStackTop(struct myStack* s) {
	if (NULL == s)return;
	if (isEmpty(s)) {
		printf("栈空！\n");
		return;
	}
	return s->parr[s->tailIdx - 1];
}

//销毁栈
void myStackDestory(struct myStack* s) {
	free(s->parr);
	free(s);
}

int main() {
	struct myStack* ms = malloc(sizeof(struct myStack));
	myStackInit(ms);
	travel(ms);
	push(ms, 1);
	push(ms, 1);
	push(ms, 4);
	push(ms, 5);
	push(ms, 1);
	push(ms, 4);
	push(ms, 1);
	push(ms, 3);
	push(ms, 1);
	push(ms, 4);
	push(ms, 5);
	push(ms, 2);
	push(ms, 1);
	printf("当前栈元素个数：%d\n", myStackSize(ms));
	printf("当前栈顶元素数据：%d\n", myStackTop(ms));
	travel(ms);
	for (int i = 0; i < 12; i++)
	{
		pop(ms);
		printf("当前栈元素个数：%d\n", myStackSize(ms));
	}
	myStackDestory(ms);
	return 0;
}