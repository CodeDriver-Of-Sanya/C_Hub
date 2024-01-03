#include "Res.h"

//创建树节点
struct Node* createNode(struct Zifu* pzf);

//根据字典创建哈夫曼树
struct Node* createHFMTree(struct Zidian* pzd);

//判断是否是叶子节点
bool isLeaf(struct Node* pRoot);

int main()
{
	struct Zidian zd = { 0 };
	//打开待解压文件
	FILE* fpSrc = fopen("2.txt", "rb");//待解压文件
	FILE* fpDst = fopen("3.txt", "wb");//解压后文件
	//把字典读出来
	fread(&zd, 1, sizeof(struct Zidian), fpSrc);
	//根据字典生成哈夫曼树
	struct Node* pRoot = createHFMTree(&zd);

	int num_zf = pRoot->zf.cnt;
	char read_c;
	int idx_read_c;
	struct Node* pTemp = pRoot;
	while (1 == fread(&read_c, 1, 1, fpSrc) && num_zf > 0)
	{
		idx_read_c = 0;
		while (idx_read_c < 8)
		{
			//0x80 = 1000 0000
			if (read_c & (0x80>>idx_read_c))
			{
				pTemp = pTemp->pLeft;
			}
			else
			{
				pTemp = pTemp->pRight;
			}
			idx_read_c++;

			if (isLeaf(pTemp))
			{
				fwrite(&(pTemp->zf.zf), 1, 1, fpDst);
				pTemp = pRoot;//从根重新开始
				num_zf--;
				if (num_zf <= 0)break;
			}
		}//end of while (idx_read_c < 8)
	}//end of while (1 == fread(&read_c, 1, 1, fpSrc) && num_zf > 0)

	fclose(fpSrc);
	fclose(fpDst);
	while (1);

	return 0;
}

struct Node* createNode(struct Zifu* pzf)
{
	struct Node* pNew = calloc(1, sizeof(struct Node));
	if (NULL == pNew)return NULL;

	memcpy(&(pNew->zf), pzf, sizeof(struct Zifu));

	return pNew;
}

struct Node* createHFMTree(struct Zidian* pzd)
{
	//0 准备个数组，存放 由字典中字符创建的每个子节点指针
	struct Node** ppArr = calloc(pzd->zf_num, sizeof(struct Node*));
	if (!ppArr)return NULL;
	for (int i = 0; i < pzd->zf_num; i++)
	{
		ppArr[i] = createNode(&(pzd->zf_arr[i]));
		ppArr[i]->zf.idx = i;
	}
	// 
	// 1 循环找最小的
	//		找第二小的
	//		放入数组
	int minIdx, secMinIdx;
	struct Node* pTemp = NULL;
	for (int i = 0; i < pzd->zf_num - 1; i++)
	{
		//找最小
		int j = 0;//假设第一个最小
		while (ppArr[j] == NULL)j++;//跳过空节点的第一个
		minIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[minIdx]->zf.cnt)
			{
				minIdx = j;
			}
		}
		//找第二小
		j = 0;
		while (ppArr[j] == NULL || j == minIdx)j++;
		secMinIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[secMinIdx]->zf.cnt && j != minIdx)
			{
				secMinIdx = j;
			}
		}

		// 2 组成树
		struct Zifu tempZf = { 0 };
		tempZf.cnt = ppArr[minIdx]->zf.cnt + ppArr[secMinIdx]->zf.cnt;
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		pTemp->pLeft = ppArr[minIdx];
		pTemp->pRight = ppArr[secMinIdx];
		ppArr[minIdx]->pParent = pTemp;
		ppArr[secMinIdx]->pParent = pTemp;

		// 3 从数组中删掉已经组成树的两个节点，组成树的空父节点放入数组
		ppArr[minIdx] = pTemp;
		ppArr[secMinIdx] = NULL;

		// 一直到循环结束
	}

	// 4 返回根节点，就是整棵树的根节点
	return pTemp;
}

bool isLeaf(struct Node* pRoot)
{
	if (NULL != pRoot && NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return true;
	}
	return false;
}