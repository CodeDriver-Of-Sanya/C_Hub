#include <stdio.h>
void nUms (int x)//创建一个分离各个位数，并隔空格打印（递归） 如输入1234，输出1 2 3 4
{
    if (x > 9)
    {
        nUms(x / 10);
    }
    printf("%d ",x % 10);
}
int main()
{
    int a = 0;
    scanf("%d" , &a);
    nUms(a);
    return 0;
}
