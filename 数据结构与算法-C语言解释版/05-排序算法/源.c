#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<stdlib.h>
#define NUM 10

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

/*选择排序：
	从待排数组中选一个最小的放到第一个位置
	最左边就是有序数组了
	再从待排数组中找最小的，放到有序数组中合适的位置（循环遍历比大小）
	整个数组选 n-1 次就有序了
*/
void select_sort(int arr[NUM], int len) {
	//选 n-1 次
	for (int i = 0; i < len-1; i++)
	{
		//从待排范围内找出最小的，放到合适范围
		//待排范围：i ~ len-1
		//合适位置：arr[i]

		//先假设待排数组中的第一个最小
		int minIdx=i;
		for (int j = i; j < len; j++) {
			if (arr[j] < arr[minIdx]) {
				minIdx = j;
			}
		}
		if (arr[minIdx] < arr[i]) {
			int temp = arr[minIdx];
			arr[minIdx] = arr[i];
			arr[i] = temp;
		}
		printf("第 %d 次:", i + 1);
		travel(arr, NUM, false);
	}
}

/*插入排序：
	直接把整个数组看成两部分
	左边包含第一个元素，是有序数组部分（一个数组天然有序）
	右边包含 n-1 个元素，是待插数组
	每次将待插数组中的第一个，插入到有序数组中，（插入后保持有序）
	如何插入：
		1.临时存储待插数据
		2.从待插数据前一个开始比较，一直到index=0
		3.如果前一个数据比待插数据大，将其往后覆盖（也可以直接两两交换，不过这样可以省一些交换步骤）
		4.若不比待插数据大，循环结束
		5.用临时数据覆盖结束位置的后一个位置

*/
void insert_sort(int arr[NUM], int len) {
	for (int i = 1; i < len; i++)
	{
		//待插数据存入临时变量
		int temp = arr[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			//如果前一个数大于待插数，往后覆盖
			if (arr[j] > temp) {
				arr[j + 1] = arr[j];
			}
			else {
				break;
			}
			
		}
		//用临时数据覆盖结束位置的后一个位置
		arr[j + 1] = temp;

		printf("第 %d 次:", i + 1);
		travel(arr, NUM, false);
	}
}

/*希尔排序
	引入步长概念，每次按照步长做排序
	步长一般默认为元素个数的一半
	步长为几就分成几组
	如果10个元素，那么步长为5
	i=0和i=5 为一组，以此类推，组内做插入排序
	接着步长再减短一半，步长变为2
	i=0,i=2,4,6,8 为一组，以此类推，组内做插入排序
	最后步长为1，整体做插入排序
*/
void shell_sort(int arr[NUM], int len) {
	//步长，一开始是元素个数的一半
	int step = len / 2;
	while (step)
	{
		//每次按照步长分组 组内做插入排序
		for (int i = step; i < len; i++)
		{
			int temp = arr[i];
			int j;
			for (j = i - step; j >= 0; j-=step) {
				if (arr[j] > temp) {
					arr[j + step] = arr[j];
				}
				else {
					break;
				}

			}
			arr[j + step] = temp;
		}
		printf("step（%d）：", step);
		travel(arr, NUM, false);
		//每次变成原来的一半
		step /= 2;
	}
}

/*基数排序
	排序算法中最快的，没有之一
	时间复杂度为O（n），且不需要比较
	排序依据：利用数组下标天然有序的性质来进行排序
	限制：
		1.只能正整数
		2.不能有重复
		3.时间复杂度可高可低
	1.申请内存创建一个数组，使其最大下标可以大过待排数组的最大数
	2.用-1填满（也可以是其他的）
	3.将元素放到新数组对应相同下标的位置
	4.再遍历不为-1的元素，放回原数组，排序完成
*/
void radix_sort(int arr[NUM], int len,int max) {
	//创建内存
	int* pTemp = malloc(sizeof(int) * (max + 1));
	//全部初始化为-1
	for (int i = 0; i < max + 1; i++) {
		pTemp[i] = -1;
	}
	//将待排数组元素放到对应下标位置
	for (int i = 0; i < len; i++) {
		pTemp[arr[i]] = arr[i];
	}
	//遍历临时内存，不为-1就覆盖回待排数组
	int k = 0;
	for (int i = 0; i < max+1; i++)
	{
		if (-1 != pTemp[i]) {
			arr[k++] = pTemp[i];
		}
	}
}

int main() {
	int arr[NUM] = { 12,66,39,48,53,72,99,1,9,41 };
	travel(arr, NUM, false);
	//printf("选择排序：\n");
	//select_sort(arr, NUM);

	//printf("插入排序：\n");
	//insert_sort(arr, NUM);

	//printf("希尔排序：\n");
	//shell_sort(arr, NUM);

	printf("基数排序：\n");
	radix_sort(arr, NUM,99);
	travel(arr, NUM, true);
	return 0;
}
