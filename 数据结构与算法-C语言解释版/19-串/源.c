#include<stdio.h>
#include<string.h>
#include<malloc.h>

/*02
串：字符串
	求长度		strlen
	赋值		strcpy
	拼接		strcat
	比较		strcmp
	找子串		strstr
两个算法：
	BF brute-force 爆破法
		i指向父串第一个字符，j指向子串第一个字符
		idx=0记录相同的开始下标，利用idx实现i回退到前进一步（一个字符）的位置
		循环比较i指向的字符和j指向的字符是否相同
			相同，i++，j++，如果加完后j=子串长度，返回idx即可（此时的idx就是子串在父串中的下标）
			不同，idx++ , i=idx,j=0,
		弊端：
			idx每次只能前进一个字符的位置
	KMP 算法
		i不还原，通过j搭配一个k来实现还原
		j往回走i和j相同的字符个数
			但如果j本身有若干个相同的，也要考虑到
			引入一个next数组，专门要有一个函数去求next数组
			next数组作用：
				next[j]=k
				j = next[j]
				k就是不相同的时候j要往前挪动的字符数量
*/

int BF(char* pStr1, char* pStr2) {
	//防呆
	if (NULL == pStr1 || NULL == pStr2)return -1;
	//i指向父串第一个字符，j指向子串第一个字符
	int i = 0;
	int j = 0;
	//idx记录相同的开始下标
	int idx = 0;
	//循环比较
	while (1)
	{
		//先考虑结束
		if ('\0' == pStr1[i] || '\0' == pStr2[j])break;
		//开始比较
		if (pStr1[i] == pStr2[j]) {
			i++;
			j++;
		}
		else {
			idx++;
			i = idx;
			j = 0;
		}
	}
	if ('\0' == pStr2[j]) {
		return idx;
	}
	return -1;
}

//创建偏移表的函数
void getNext(char* s, int* next, int size) {
	int j = 0;
	int k = -1;//普通情况，往前走一个

	next[0] = k;
	while (j < size) {
		if (-1 == k || s[k] == s[j]) {
			if (s[++j] == s[++k]) {
				next[j] = k;
			}
			else {
				next[j] = k;
			}
		}
		else {
			k = next[k];
		}
	}
}

int KMP(char* pStr1, char* pStr2) {
	//防呆
	if (NULL == pStr1 || NULL == pStr2)return -1;
	//制作next数组
	int size1 = strlen(pStr1);
	int size2 = strlen(pStr2);
	int* pNext = malloc(sizeof(int) * size2);
	getNext(pStr2, pNext, size2);
	
#if 1
	//测试
	printf("next数组：");
	for (int i = 0; i < size2; i++)
	{
		printf("%d ", pNext[i]);
	}
	printf("\n");
#endif
	int i = 0;
	int j = 0;
	while (i<size1&&j<size2)
	{
		if (pStr1[i] == pStr2[j]||-1==j) {
			i++;
			j++;
		}
		else {
			j = pNext[j];
		}
	}
	if ('\0' == pStr2[j]) {
		return (i-j);
	}

	return -1;
}

int main() {
	char str1[] = "abcdefghijk";
	char str2[] = "aaab";

	//int r = BF(str1, str2);
	int r = KMP(str1, str2);

	if (-1 == r) {
		printf("找不到字符串！\n");
	}
	else {
		printf("r:%d\n", r);
	}
	

	while (1);
	return 0;
}
