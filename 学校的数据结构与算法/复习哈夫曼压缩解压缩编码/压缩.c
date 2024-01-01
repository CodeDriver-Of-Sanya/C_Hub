#include"Res.h"

//�����ļ�
void analysisFile(char* secFile, struct Zidian* pzd);
//�������ڵ�
struct Node* createNode(struct Zifu* pzf);
//������������
struct Node* createHFMTree(struct Zidian* pzd);
//���ݹ���������ù��������� �� д���ֵ���
void createHFMCode(struct Node* pRoot, struct Zidian* pzd);
//������ѹ���ļ�������Ӧ�ַ���HFM����д��ѹ���ļ�
void writeCompressFile(const char* srcFile, const char* dstFile, struct Zidian* pzd);

int main()
{
	//��ѹ���ļ���Ϊ 1.txt

	//1.������ѹ���ļ����õ��ֵ�
	struct Zidian zd = { 0 };
	analysisFile("1.txt", &zd);
	//2.�����ֵ乹����������
	struct Node* pRoot = createHFMTree(&zd);
	//3.���ݹ���������ù��������벢д���ֵ�
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
	//0 ׼�������飬��� ���ֵ����ַ�������ÿ���ӽڵ�ָ��
	struct Node** ppArr = calloc(pzd->zf_num, sizeof(struct Node*));
	if (!ppArr)return NULL;
	for (int i = 0; i < pzd->zf_num; i++)
	{
		ppArr[i] = createNode(&(pzd->zf_arr[i]));
		ppArr[i]->zf.idx = i;
	}
	// 
	// 1 ѭ������С��
	//		�ҵڶ�С��
	//		��������
	int minIdx, secMinIdx;
	struct Node* pTemp = NULL;
	for (int i = 0; i < pzd->zf_num - 1; i++)
	{
		//����С
		int j = 0;//�����һ����С
		while (ppArr[j] == NULL)j++;//�����սڵ�ĵ�һ��
		minIdx = j++;
		for (j; j < pzd->zf_num; j++)
		{
			if (ppArr[j] && ppArr[j]->zf.cnt < ppArr[minIdx]->zf.cnt)
			{
				minIdx = j;
			}
		}
		//�ҵڶ�С
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

		// 2 �����
		struct Zifu tempZf = { 0 };
		tempZf.cnt = ppArr[minIdx]->zf.cnt + ppArr[secMinIdx]->zf.cnt;
		tempZf.idx = -1;
		pTemp = createNode(&tempZf);
		pTemp->pLeft = ppArr[minIdx];
		pTemp->pRight = ppArr[secMinIdx];
		ppArr[minIdx]->pParent = pTemp;
		ppArr[secMinIdx]->pParent = pTemp;

		// 3 ��������ɾ���Ѿ�������������ڵ㣬������Ŀո��ڵ��������
		ppArr[minIdx] = pTemp;
		ppArr[secMinIdx] = NULL;

		// һֱ��ѭ������
	}
	
	// 4 ���ظ��ڵ㣬�����������ĸ��ڵ�
	return pTemp;
}


//�ж��Ƿ���Ҷ�ӽڵ�
bool isLeaf(struct Node* pRoot)
{
	if (NULL != pRoot && NULL == pRoot->pLeft && NULL == pRoot->pRight)
	{
		return true;
	}
	return false;
}

//����HFM����
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
