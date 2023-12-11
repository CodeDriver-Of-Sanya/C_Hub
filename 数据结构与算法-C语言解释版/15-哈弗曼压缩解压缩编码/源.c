#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include"res.h"

//day16-04

/*
哈夫曼(huffman)树：被称为最佳搜索树，整体搜索效率最高
	出现频率高的，距离根节点近,对应的哈夫曼编码短
	出现频率低的，距离根节点远，对应的哈夫曼编码长
	将所有数据放到叶子节点，往左分支去一次记0，往右分支去一次记1
	如果都用哈夫曼编码去描述数据，最终用哈夫曼编码描述的数据相对压缩了许多

	压缩：
		1.分析待压缩文件->得到字典
			1.0文件操作
			1.1要知道有多少种字节
			1.2知道每种字节出现多少次
		2.根据字典生成哈夫曼树并获取每个字节对应的哈夫曼编码
			遍历整棵树，过程中存储往左（1）还是往右（2），遇到叶子节点就存储
		3.创建压缩文件（字典写入），读取待压缩文件，一个一个字节的获取对应的编码（二进制位）拼接成字节并写入到压缩后文件中
		4.遍历完就写完了，关闭文件即可

	解压：
		1.从压缩后文件中把字典读出来
		2.根据字典生成哈夫曼树
		3.循环从压缩后文件中读取字节
			3.1一个个比特位分析，去哈夫曼树中找
			3.2找到一个叶子节点，就得到一个字节的解压后的数据，顺便写入解压后的文件中
			3.3如果读取完毕，或者没有孩子了还往左或者往右，就结束
*/

//分析待压缩文件，得到字典
void analysisFile(char* srcFile, struct AllZiFu* pZd) {
	//防呆
	if (NULL == srcFile || NULL == pZd)return ;

	//1.打开文件
	FILE* fp = fopen(srcFile, "rb");
	if (NULL == fp) {
		printf("文件打开失败！\n");
		return;
	}
	//2.循环读取
	//将读到的字节存在这里
	unsigned char c;
	int r;
	//在字典中是否存在的标记，默认不存在
	bool exist = false;
	int i;
	while (true)
	{
		r = fread(&c, 1, 1, fp);
		if (r < 1)break;
		//3.看字典中是否存在这个字符
		
		for (i = 0; i < pZd->num; i++)
		{
			if (c == pZd->arr[i].zf) {
				exist = true;
				break;
			}
		}
		//存在	出现次数+1
		if (exist) {
			pZd->arr[i].cnt++;
			exist = false;
		}
		else {//不存在	添加到字典中
			pZd->arr[pZd->num].zf = c;
			pZd->arr[pZd->num].cnt++;
			pZd->num++;
		}

		
	}
	
	//4.关闭文件
	fclose(fp);
}

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
	for (int i = 0; i < pZd->num-1; i++)
	{
		//1.找到出现频率最低的
		//假设第一个最小
		j = 0;
		while (pArray[j] == NULL)j++;//找到第一个
		minIdx = j;

		for ( j = 0; j < pZd->num; j++)//遍历整个数组
		{
			if (pArray[j] &&
				pArray[j]->data.cnt < pArray[minIdx]->data.cnt) {
				minIdx = j;
			}
		}

		//2.找到出现频率第二低的
		j = 0;
		while (pArray[j] == NULL||j==minIdx)j++;//找到第二个
		secMinIdx = j;

		for (j = 0; j < pZd->num; j++)//遍历整个数组
		{
			if (pArray[j] &&
				j!=minIdx&&
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

//设置haffman编码
void setHaffmanCode(struct node* root, char* haffmanCode) {
	char buff[HFM_CODE_LEN] = { 0 };
	int idx = 0;
	//root 循环找父
	while (root->pParent)
	{
		//过程中判断是其父的左孩子还是右孩子，存到数组里
		if (root == root->pParent->pL) {//是左孩子
			buff[idx++] = 1;
		}
		else {//是右孩子
			buff[idx++] = 2;
		}


		root = root->pParent;
	}
	

	//调转并写入haffmanCode数组中
	for (int i = 0; i < idx; i++)
	{
		haffmanCode[i] = buff[idx - i - 1];
	}
}

//根据哈夫曼树得到哈夫曼编码并写入字典中
void createHaffmanCode(struct node* root, struct AllZiFu* pZd) {
	int idx;
	if (root) {
		if (isLeaf(root)) {//说明是叶子节点
			idx = root->data.idx;
			setHaffmanCode(root, pZd->arr[idx].code);
		}
		else {//不是叶子节点
			createHaffmanCode(root->pL, pZd);
			createHaffmanCode(root->pR, pZd);
		}
	}
}

//从字典中，得到一个字符对应的哈夫曼编码
void getHaffmanCode(char c, char* haffmanCode, struct AllZiFu* pzd) {
	for (int i = 0; i < pzd->num ; i++)
	{
		if (c == pzd->arr[i].zf) {
			strcpy(haffmanCode, pzd->arr[i].code);
			return;
		}
	}
}

//遍历待压缩文件，并把待压缩文件中字符对应的哈夫曼编码写入压缩后的文件中
void writeCompressFile(const char* srcFile, const char* dstFile, struct ALLZiFu* pzd) {
	//1.打开待压缩文件 创建压缩后文件
	FILE* fpSrc = fopen(srcFile, "rb");
	FILE* fpDist = fopen(dstFile, "wb");
	if (NULL == fpDist || NULL == fpSrc)return;

	//2.写入字典
	fwrite(pzd, 1, sizeof(struct AllZiFu), fpDist);

	//3.循环读待压缩文件 读完循环结束
	char c;//存储读到的字节
	int r;

	char charForWrite;//用来写入的字节，一个个比特位拼起来的
	char idxForWrite;//charForWrite的索引（下标）

	char haffmanCode[HFM_CODE_LEN] = {0};//临时存储hfm编码
	int idxForHaffmanCode = 0;

	bool isEnd = false;//标记是否读完

	while (1) {
		if (0 == haffmanCode[idxForHaffmanCode]) {//需要读的时候再读
			r = fread(&c, 1, 1, fpSrc);
			if (r < 1) {
				break;
			}

			getHaffmanCode(c, haffmanCode, pzd);//从字典中获取C字符对应的haffman编码，并写入到 haffmanCode 数组中
			idxForHaffmanCode = 0;

		}
		
		//4.得到字符对应的编码，拼成二进制字节，满八个比特位写入一次
		charForWrite = 0;
		idxForHaffmanCode = 0;
		idxForWrite = 0;
		while (idxForHaffmanCode<8)
		{
			if (2 == haffmanCode[idxForHaffmanCode]) {//设置对应比特位为0
				charForWrite &= ~(1 << (7 - idxForWrite));

				idxForHaffmanCode++;
				idxForWrite++;
			}
			else if (1 == haffmanCode[idxForHaffmanCode]) {//设置对应比特位为1
				charForWrite |= (1 << (7 - idxForWrite));

				idxForHaffmanCode++;
				idxForWrite++;
			}
			else {//当前字节对应的haffman编码已经读完了
				r = fread(&c, 1, 1, fpSrc);
				if (r < 1) {
					isEnd = true;
					break;
				}
				getHaffmanCode(c, haffmanCode, pzd);//从字典中获取C字符对应的haffman编码，并写入到 haffmanCode 数组中
				idxForHaffmanCode = 0;
			}
		}//end of while (idxForHaffmanCode<8)
		//满8个比特位，写一次
		fwrite(&charForWrite, 1, 1, fpDist);

		for (int i = 0; i < 8; i++)
		{
			if (charForWrite & 0x80) {
				printf("1");
			}
			else {
				printf("0");
			}
			charForWrite <<= 1;
		}

		if (isEnd)break;
	}//end of while (1)


	//5.关闭保存
	fclose(fpDist);
	fclose(fpSrc);
}

int main() {
	//待压缩文件名  1.txt  aaaaaabbbbbbbbbbbcccdedefghabchhh

	//创建字典结构体
	struct AllZiFu zd = { 0 };

	analysisFile("1.txt", &zd);

	struct node* tree = createHaffmanTree(&zd);

	createHaffmanCode(tree, &zd);

	writeCompressFile("1.txt", "2.txt", &zd);

	while (1);
	return 0;
}
