#include"Res.h"

//分析待压缩文件，生成字典
void analysisFile(char* secFile, struct Zidian* pzd);
//根据字符创建哈夫曼树节点
struct Node* createNode(struct Zifu* pzf);
//根据字典构建哈夫曼树
struct Node* createHFMTree(struct Zidian* pzd);
//根据哈夫曼树获得哈夫曼编码 并 写入字典中
void createHFMCode(struct Node* pRoot, struct Zidian* pzd);
//遍历待压缩文件，根据字典将对应字符的HFM编码写入压缩后文件
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
	//4.根据哈夫曼编码生成压缩后的文件
	writeCompressFile("1.txt", "2.txt", &zd);

	while (1);

	return 0;
}

void analysisFile(char* secFile, struct Zidian* pzd)
{
	if (secFile == NULL || pzd == NULL)return;//防呆

	FILE* fp = fopen(secFile, "rb");//以二进制只读的方式打开文件
	if (NULL == fp)
	{
		perror("analysisFile open file failed!\n");
		return;
	}

	unsigned char read_c;//用于存储读取到的字符
	while (fread(&read_c, 1, 1, fp)==1)//如果读到一个字符
	{
		bool exist = false;//是否已经在字典中存在
		for (int i = 0; i < pzd->zf_num; i++)
		{
			if (read_c == pzd->zf_arr[i].zf)
			{
				exist = true;
				pzd->zf_arr[i].cnt++;//如果存在，该字符的出现次数+1
			}
		}
		if (!exist)//如果不存在，在字典中存入该字符并且出现次数+1
		{
			pzd->zf_arr[pzd->zf_num].zf = read_c;
			pzd->zf_arr[pzd->zf_num++].cnt++;
		}
	}//end of (fread(&read_c, 1, 1, fp)==1
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
	//0 准备个数组，存放 根据字典创建的 每个字符的 节点指针
	struct Node** ppArr = calloc(pzd->zf_num, sizeof(struct Node*));
	if (!ppArr)return NULL;
	//根据字典创建 每个字符的 节点指针 并放入刚才创建的指针数组
	for (int i = 0; i < pzd->zf_num; i++)
	{
		ppArr[i] = createNode(&(pzd->zf_arr[i]));
		ppArr[i]->zf.idx = i;//存入与指针数组所对应的数组下标
	}
	// 1 在 指针数组中 循环 找最小的和第二小，组合成树放入指针数组
	int minIdx, secMinIdx;
	struct Node* pTemp = NULL;
	for (int i = 0; i < pzd->zf_num - 1; i++)
	{
		//找最小
		int j = 0;//假设第一个最小
		while (ppArr[j] == NULL)j++;//跳过空节点
		minIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			//如果该节点存在 且 j出现次数 小于 minIdx的
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[minIdx]->zf.cnt)
			{
				minIdx = j;
			}
		}
		//找第二小
		j = 0;
		while (ppArr[j] == NULL || j == minIdx)j++;//跳过空和最小节点
		secMinIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[secMinIdx]->zf.cnt 
				&& j != minIdx)
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
	}//end of (int i = 0; i < pzd->zf_num - 1; i++)
	// 4 返回最后的根节点，就是整棵树的根节点
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
	while (pRoot->pParent)//从叶子节点往回找父节点
	{
		//左1右2
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
		//由于是逆向寻找的，所以需要把字符串逆序一遍
		pCodeArr[i] = tempCodeArr[tempIdx - 1 - i];
	}
}

void createHFMCode(struct Node* pRoot, struct Zidian* pzd)
{
	if (pRoot == NULL || pzd == NULL)return;
	if (isLeaf(pRoot))
	{
		int idx = pRoot->zf.idx;
		setHFMCode(pRoot, pzd->zf_arr[idx].code);
	}
	else
	{
		createHFMCode(pRoot->pLeft, pzd);
		createHFMCode(pRoot->pRight, pzd);
	}

}

//从字典中得到对应字符的哈夫曼编码
void getHFMCode(char read_c, char* tempHFMCode, struct Zidian* pzd)
{
	for (int i = 0; i < pzd->zf_num; i++)
	{
		if (read_c == pzd->zf_arr[i].zf)
		{
			strcpy(tempHFMCode, pzd->zf_arr[i].code);

			//测试输出
			//printf("%c---", read_c);
			//for (int j = 0; j < HFM_CODE_LEN; j++)
			//{
			//	if (tempHFMCode[j] != 0)
			//	{
			//		printf("%d", tempHFMCode[j]);
			//	}
			//}
			//printf("\n");

			return;
		}
	}
}

void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd)
{
	if (NULL == srcFile || NULL == dstFile || NULL == pzd)return;
	FILE* fpDst = fopen(dstFile, "wb");
	FILE* fpSrc = fopen(srcFile, "rb");

	fwrite(pzd, 1, sizeof(struct Zidian), fpDst);

	char read_c;//存储读到的字节
	int retRead;
	char write_c;//存储要写入的字节
	int idx_write_c;//统计读到了几个bit位到write_c中

	char tempHFMCode[HFM_CODE_LEN] = { 0 };//临时存储哈夫曼编码
	int idxTempHFMCode = 0;

	bool isEnd = false;
	while (!isEnd)
	{
		//如果临时哈夫曼编码数组是空的就去新读一个
		if (0 == tempHFMCode[idxTempHFMCode])
		{
			retRead = fread(&read_c, 1, 1, fpSrc);
			if (retRead < 1)break;
			//从字典中获取read_c字符的HFM编码写入到tempHFMCode中
			getHFMCode(read_c, tempHFMCode, pzd);
			idxTempHFMCode = 0;
		}

		//拼成二进制字节
		write_c = 0;
		idx_write_c = 0;
		while (idx_write_c < 8)
		{
			if (2 == tempHFMCode[idxTempHFMCode])//设置对应bit位为0
			{
				//~表示按位取反
				//1&？，？不变
				//0&？，？都变0
				write_c = write_c & ~(1 << (7 - idx_write_c));
				idx_write_c++;
				idxTempHFMCode++;
			}
			else if (1 == tempHFMCode[idxTempHFMCode])//设置对应bit位为1
			{
				//1|？，？都变1
				//0|？，？不变
				write_c = write_c | (1 << (7 - idx_write_c));
				idx_write_c++;
				idxTempHFMCode++;
			}
			else
			{
				//到这就说明当前字节的HFM编码已经读完了
				//需要新读一个
				retRead = fread(&read_c, 1, 1, fpSrc);
				if (retRead < 1)
				{
					//读不到说明待压缩文件已经读取完毕了，可以结束了
					isEnd = true;
					break;
				}
				getHFMCode(read_c, tempHFMCode, pzd);
				idxTempHFMCode = 0;
			}
		}//end of while (idx_write_c < 8)
		//满八个bit位，写一次
		fwrite(&write_c, 1, 1, fpDst);

		//测试用例
		//for (int i = 0; i < 8; i++)
		//{
		//	if (write_c & 0x80)
		//	{
		//		printf("1");
		//	}
		//	else
		//	{
		//		printf("0");
		//	}
		//	write_c <<= 1;
		//}
		//printf("\n");

	}//end of while (!isEnd)

	//写完了
	fclose(fpDst);
	fclose(fpSrc);
}
