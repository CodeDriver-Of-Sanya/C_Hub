#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct myQueue {
	int* parr;
	int headIdx;
	int tailIdx;
	int capacity;
};

//初始化
void initQueue(struct myQueue* q) {
	q->capacity = 10;
	q->parr = malloc(q->capacity * sizeof(int));
	q->headIdx = q->tailIdx = 0;
}

//队列是否为空
bool isEmpty(struct myQueue* q) {
	if (NULL == q)return;
	if (q->headIdx == q->tailIdx) {
		return true;
	}
	else {
		return false;
	}
}

//队列中的元素个数
int sizeQueue(struct myQueue* q) {
	if (NULL == q)return;
	return (q->tailIdx - q->headIdx);
}

//入队
void push(struct myQueue* q,int data) {
	if (NULL == q)return;
	if (q->tailIdx >= q->capacity) {
		printf("队满，无法插入！\n");
		return;
	}
	q->parr[q->tailIdx++] = data;
	printf("插入成功\n");
}

//出队
void pop(struct myQueue* q) {
	if (NULL == q)return;
	if (isEmpty(q)) {
		printf("队空，无法删除！\n");
		return;
	}
	q->headIdx++;
}

//遍历
void travel(struct myQueue* q) {
	if (NULL == q)return;
	if (isEmpty(q)) {
		printf("队空，\n");
		return;
	}
	for (int i = q->headIdx; i < q->tailIdx; i++)
	{
		printf("%d ", q->parr[i]);
	}
	printf("\n");
}

//销毁
void destory(struct myQueue* q) {
	if (NULL == q)return;
	free(q->parr);
	free(q);
}

int main() {
	struct myQueue* q = malloc(sizeof(struct myQueue));
	initQueue(q);
	travel(q);
	push(q, 1);
	push(q, 1);
	push(q, 4);
	push(q, 5);
	push(q, 1);
	push(q, 4);
	push(q, 1);
	push(q, 3);
	push(q, 1);
	push(q, 4);
	push(q, 5);
	push(q, 2);
	push(q, 1);
	printf("当前栈元素个数：%d\n", sizeQueue(q));
	travel(q);
	for (int i = q->headIdx; i < q->tailIdx; i++)
	{
		pop(q);
		printf("当前栈元素个数：%d\n", sizeQueue(q));
		travel(q);
	}
	destory(q);
	return 0;
}