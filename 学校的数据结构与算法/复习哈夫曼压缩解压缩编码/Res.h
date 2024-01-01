#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define HFM_CODE_LEN 10//设置哈夫曼编码长度

//字符类型
struct Zifu
{
	unsigned char zf;//字符
	unsigned int cnt;//出现次数
	char code[HFM_CODE_LEN];//对应的哈夫曼编码
	int idx;//下标
};
//字典类型
struct Zidian
{
	int zf_num;//字符数量
	struct Zifu zf_arr[256];//存储每种字符的信息（最多256种）
};
//哈夫曼书节点类型
struct Node
{
	struct Zifu zf;
	struct Node* pLeft;
	struct Node* pRight;
	struct Node* pParent;
};