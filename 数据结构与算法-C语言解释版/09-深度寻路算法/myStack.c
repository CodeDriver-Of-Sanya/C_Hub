#include "myStack.h"
#include"res.h"
#include<stdio.h>
#include<malloc.h>
#include<string.h>

void init(myStack* s)
{
	if (NULL == s)return;
	s->pBuff = NULL;
	s->len = s->maxlen = 0;
}

void push(myStack* s, myPoint* p)
{
	if (NULL == s || NULL == p)return;
	if (s->maxlen <= s->len) {
		s->maxlen = s->maxlen + (((s->maxlen / 2) > 1) ? (s->maxlen / 2) : 1);
	}
	myPoint* pNew = malloc(s->maxlen * sizeof(myPoint));
	if (s->pBuff) {
		memcpy(pNew, s->pBuff, s->len * sizeof(myPoint));
		free(s->pBuff);
	}
	s->pBuff = pNew;
	s->pBuff[s->len].col = p->col;
	s->pBuff[s->len].row = p->row;
	s->len++;
}

void pop(myStack* s)
{
	if (NULL == s)return;
	if (s->len > 0) {
		s->len--;
	}
}

myPoint* getTop(myStack* s)
{
	if (NULL == s)return;
	return s->pBuff+(s->len-1);
}

bool isEmpty(myStack* s)
{
	if (NULL == s)return true;
	return (s->len == 0);
}
