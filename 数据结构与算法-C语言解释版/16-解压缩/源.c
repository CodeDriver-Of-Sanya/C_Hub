#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"res.h"

//创建树节点
struct node* createNode(struct ZiFu* pZf) {
	struct node* pNew = malloc(sizeof(struct node));
	if (NULL == pNew) {
		return NULL;
	}
	memset(pNew, 0, sizeof(struct node));
	memcpy(&(pNew->data), pZf, sizeof(struct ZiFu));
	return pNew;
}

//根据字典构建哈夫曼树
struct node* createHaffmanTree(struct AllZiFu* pZd) {
	//准备个数组
	struct node** pArray = (struct node**)malloc(pZd->num * (sizeof(struct node*)));
	if (NULL == pArray)return NULL;

	for (int i = 0; i < pZd->num; i++)
	{
		pArray[i] = createNode(&(pZd->arr[i]));
		pArray[i]->data.idx = i;//数组下标
	}

	int minIdx, secMinIdx;
	int j;
	struct node* pTemp = NULL;
	//循环找
	for (int i = 0; i < pZd->num - 1; i++)
	{
		//1.找到出现频率最低的
		//假设第一个最小
		j = 0;
		while (pArray[j] == NULL)j++;//找到第一个
		minIdx = j;

		for (j = 0; j < pZd->num; j++)//遍历整个数组
		{
			if (pArray[j] &&
				pArray[j]->data.cnt < pArray[minIdx]->data.cnt) {
				minIdx = j;
			}
		}

		//2.找到出现频率第二低的
		j = 0;
		while (pArray[j] == NULL || j == minIdx)j++;//找到第二个
		secMinIdx = j;

		for (j = 0; j < pZd->num; j++)//遍历整个数组
		{
			if (pArray[j] &&
				j != minIdx &&
				pArray[j]->data.cnt < pArray[secMinIdx]->data.cnt) {
				secMinIdx = j;
			}
		}

		//3.组成树

		//生成父节点
		struct ZiFu tempZf = { 0,pArray[secMinIdx]->data.cnt + pArray[minIdx]->data.cnt };
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		//构建
		pTemp->pL = pArray[minIdx];
		pTemp->pR = pArray[secMinIdx];
		pArray[minIdx]->pParent = pTemp;
		pArray[secMinIdx]->pParent = pTemp;

		//4.数组中删掉出现频率最低的和出现频率第二低的，添加新的父节点
		pArray[minIdx] = pTemp;//即删除了最小频率节点又添加了父节点
		pArray[secMinIdx] = NULL;
	}


	//5.返回根节点
	return pTemp;
}

//判断是否为叶子节点
bool isLeaf(struct node* root) {
	if (root && NULL == root->pL && NULL == root->pR) return true;
	return false;
}

int main() {
	//创建字典结构体
	struct AllZiFu zd = { 0 };

	FILE* fpsrc = fopen("2.txt", "rb");
	FILE* fpdist = fopen("3.txt", "wb");//解压后文件

	//字典读出来
	fread(&zd, 1, sizeof(struct AllZiFu), fpsrc);

	//根据字典生成哈夫曼树
	struct node* pRoot = createHaffmanTree(&zd);

	//统计字节数
	int allCnt = pRoot->data.cnt;
	int myCount = 0;

	char temp;//读到的字节
	struct node* pTemp = pRoot;

	int idx;//比特位的索引
	bool isOK = false;
	while (1==fread(&temp,1,1,fpsrc))
	{
		idx = 0;
		while (idx < 8) {
			if ( temp&(0x80>>idx) ) {//当前位为1
				pTemp = pTemp->pL;
			}
			else {//当前位为0
				pTemp = pTemp->pR;
			}

			if (isLeaf(pTemp)) {//如果是叶子节点
				fwrite(&(pTemp->data.zf),1,1,fpdist);
				myCount++;
				if (myCount >= allCnt) {
					isOK = true;
					break;
				}
				pTemp = pRoot;//回到根节点
			}
			idx++;//idx变化
		}//end of while (idx < 8)
		if (isOK) {
			break;
		}
	}//end of (1==fread(&temp,1,1,fpsrc))

	fclose(fpsrc);
	fclose(fpdist);
	return 0;
}
