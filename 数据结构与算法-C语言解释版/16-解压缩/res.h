#pragma once
//哈夫曼编码长度限制
#define HFM_CODE_LEN 10

//字符类型
struct ZiFu {
	//存储字符本身
	unsigned char		zf;
	//该字符的出现次数
	unsigned int		cnt;
	//哈夫曼编码
	char				code[HFM_CODE_LEN];
	//数组下标
	int					idx;
};

//字典类型
struct AllZiFu {
	//总共的字符数量
	int num;
	//每个字符的信息（字符汇总,字符类型最多256种）
	struct ZiFu arr[256];
};

//树的节点类型
struct node
{
	struct ZiFu data;
	struct node* pParent;
	struct node* pL;
	struct node* pR;
};
