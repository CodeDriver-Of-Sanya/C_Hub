#include<stdio.h>

int main ()
{   
    printf("请输入4位数字：");
    int arrZ[4] = {1000,100,10,1};//创建用于分离各位数值的数组
    int num = 0;
    scanf("%d", &num);//将输入的数值赋值到num整形变量之上
    int i = 0;
    int arr[4] = {};//用于接收分离后，各位的数值
    while (i < 4)//用于分离千，百，十，个，位的数值，并赋到arr的4个数组当中
    {
        
        arr[i] = num / arrZ[i];
        num = num - (num / arrZ[i] * arrZ[i]);
        i++;
    }
    printf("各位数之和为：");
    int Z = arr[0]+arr[1]+arr[2]+arr[3];
    if (Z > 0)//如果数值为负数，则进行改为正数的变换
    printf("%d", Z);//进行各位数值之和的打印
    else
    printf("%d", -1 * Z);
    
    
    printf("\n");
    

    return 0;
}
