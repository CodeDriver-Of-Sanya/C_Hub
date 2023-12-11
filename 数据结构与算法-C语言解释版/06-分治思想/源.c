#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>

#define NUM 11
#define AREA 1000
#define BUCKET_NUM 10

void travel(int arr[NUM], int len, bool isAfter) {
	if (isAfter) {
		printf("after sort:");
	}
	else {
		printf("before sort:");
	}

	for (int i = 0; i < len; i++)
	{
		printf("%02d ", arr[i]);
	}

	printf("\n");
}

/*桶（箱）排序
	把数据分成若干份，每一份中，用其他的排序方式（比如插入排序）
	假设数据都是三位数，每一位上的数字都是0~9，所以可以分成十个桶
	因为有极端情况，桶的大小应该是数组大小
	十个桶编号0~9，数据全部初始化为-1
	第一次先看个位
		个位是多少，就放到对应编号的相同索引下
		再顺着从桶中取出覆盖原来数组
	第二次看十位
		放入取出原则同上
	第三次看百位
		放入取出原则同上
	排序结束

*/
void bucket_sort(int arr[NUM], int len) {
	//循环n次
	int area = 1;
	while (area<AREA)
	{
		int data;
		//准备十个桶(二维数组)
		int* pArr = malloc(sizeof(int) * (BUCKET_NUM * NUM));
		//全部初始化为-1
		memset(pArr, -1, sizeof(int) * (BUCKET_NUM * NUM));
		//数组到桶里
		for (int i = 0; i < len; i++)
		{
			data = arr[i] / area % 10;//这个用来作为二维数组的下标
			pArr[data * NUM + i] = arr[i];
		}
		//数组到桶里
		for (int i = 0,k=0; i < BUCKET_NUM*NUM; i++)
		{
			if (-1 != pArr[i]) {
				arr[k++] = pArr[i];
			}
		}
		travel(arr, NUM, false);
		area *= 10;
	}
}

/*二分查找
	一次排除一半
*/
int halfFind(int arr[NUM], int len, int data) {
	//找到了返回元素下标，找不到返回-1
	//左边下标
	int left = 0;
	//右边下标
	int right = len - 1;
	//中间下标
	int m = (left + right) / 2;
	while (true)
	{
		if (left > right) {
			return -1;
		}
		if (data == arr[m]) {
			//找到了
			return m;
		}
		if (data > arr[m]) {
			left = m + 1;
			m = (left + right) / 2;
		}
		if(data < arr[m]){
			right = m - 1;
			m = (left + right) / 2;
		}
	}

}

/*快速排序
	把数据分成两组进行排序
	先假定一个中间数据
	如果假定左边的时中间数据，那么先挪动右边的数
	让左边的都要比中间数据小，右边的都比中间数据大
	进行递归
	左边再继续分组，右边再继续分组
	分到每组只有一个数据时，整体就有序了
	具体步骤
		1.临时保存中间数据
		2.如果右>左&&右>中间：右往前挪动一位
			否则：用右覆盖左
			若左<右&&左<中间值：左往后挪动一位
			否则：用左覆盖右
		直到左与右合拢，用临时保存的中间值覆盖并结束循环
			若左>右，循环结束
*/

void quickSort(int arr[NUM], int left, int right) {
	//结束条件
	if (left >= right) {
		return;
	}
	printf("left:%d  right:%d\n", left, right);
	//临时保存中间数据
	int temp = arr[left];
	//用另外两个变量代表left和right
	int L = left;
	int R = right;
	//循环直到left和right合拢
	while (L < R) {
		while (L<R && arr[R]>temp) {
			R--;
		}
		arr[L] = arr[R];
		while (L < R && arr[L] < temp) {
			L++;
		}
		arr[R] = arr[L];
	}
	arr[L] = temp;
	travel(arr, NUM, false);
	//左边的递归
	quickSort(arr, left, L - 1);
	//右边的递归
	quickSort(arr, L + 1, right);
}

void quick_sort(int arr[NUM], int len) {
	quickSort(arr, 0, len - 1);
}


int main() {
	int arr[NUM] = { 999,327,666,114,514,321,250,888,168,110,985 };
	travel(arr, NUM, false);

	//printf("桶（箱）排序：\n");
	//bucket_sort(arr, NUM);

	printf("快速排序：\n");
	quick_sort(arr, NUM);

	travel(arr, NUM, true);

	//待搜索数据
	//int n;
	//结果
	//int ret;
	//while (true)
	//{
	//	printf("请输入要查找的数据：");
	//	scanf("%d", &n);
	//	ret = halfFind(arr, NUM, n);
	//	if (ret < 0) {
	//		printf("没找到 %d 这个数\n", n);
	//	}
	//	else {
	//		printf("arr[%d]:%d\n", ret, arr[ret]);
	//	}
	//}

	return 0;
}