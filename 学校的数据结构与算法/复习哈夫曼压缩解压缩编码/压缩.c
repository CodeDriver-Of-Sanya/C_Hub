#include"Res.h"

//分析文件
void analysisFile(char* secFile, struct Zidian* pzd);
//创建树节点
struct Node* createNode(struct Zifu* pzf);
//构建哈夫曼树
struct Node* createHFMTree(struct Zidian* pzd);
//根据哈夫曼树获得哈夫曼编码 并 写入字典中
void createHFMCode(struct Node* pRoot, struct Zidian* pzd);
//遍历待压缩文件，将对应字符的HFM编码写入压缩文件
void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd);

int main()
{
	//待压缩文件名为 1.txt

	//1.分析待压缩文件，得到字典
	struct Zidian zd = { 0 };
	analysisFile("1.txt", &zd);
	//2.根据字典构建哈夫曼树
	struct Node* pRoot = createHFMTree(&zd);
	//3.根据哈夫曼树获得哈夫曼编码并写入字典
	createHFMCode(pRoot, &zd);

	while (1);

	return 0;
}

void analysisFile(char* secFile, struct Zidian* pzd)
{
	if (secFile == NULL || pzd == NULL)return;

	FILE* fp = fopen(secFile, "rb");
	if (NULL == fp)
	{
		perror("analysisFile open file failed!\n");
		return;
	}

	unsigned char read_c;
	while (fread(&read_c, 1, 1, fp)==1)
	{
		bool exist = false;
		for (int i = 0; i < pzd->zf_num; i++)
		{
			if (read_c == pzd->zf_arr[i].zf)
			{
				exist = true;
				pzd->zf_arr[i].cnt++;
			}
		}

		if (!exist)
		{
			pzd->zf_arr[pzd->zf_num].zf = read_c;
			pzd->zf_arr[pzd->zf_num++].cnt++;
		}
		
	}

	fclose(fp);
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


//判断是否是叶子节点
bool isLeaf(struct Node* pRoot)
{
	if (NULL != pRoot && NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return true;
	}
	return false;
}

//设置HFM编码
void setHFMCode(struct Node* pRoot, char* pCodeArr)
{
	char tempCodeArr[HFM_CODE_LEN] = { 0 };
	int tempIdx = 0;
	while (pRoot->pParent)
	{
		if (pRoot == pRoot->pParent->pLeft)
		{
			tempCodeArr[tempIdx++] = 1;
		}
		else
		{
			tempCodeArr[tempIdx++] = 2;
		}
		pRoot = pRoot->pParent;
	}
	for (int i = 0; i < tempIdx; i++)
	{
		pCodeArr[i] = tempCodeArr[tempIdx - 1 - i];
	}
}

void createHFMCode(struct Node* pRoot, struct Zidian* pzd)
{
	if (pRoot == NULL || pzd == NULL)return;
	int idx;
	if (isLeaf(pRoot))
	{
		idx = pRoot->zf.idx;
		setHFMCode(pRoot, pzd->zf_arr[idx].code);
	}
	else
	{
		createHFMCode(pRoot->pLeft, pzd);
		createHFMCode(pRoot->pRight, pzd);
	}

}

void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd)
{
	if (NULL == srcFile || NULL == dstFile || NULL == pzd)return;
	FILE* fpDst = fopen(dstFile, "wb");
	FILE* fpSrc = fopen(srcFile, "rb");

	fwrite(pzd, 1, sizeof(struct Zidian), fpDst);


}
