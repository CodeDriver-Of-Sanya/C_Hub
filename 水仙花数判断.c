#include <stdio.h>
#include <math.h>

int Pan_ShuiXian (int Num)
{
    if(Num > 9)
    {
        return Pan_ShuiXian(Num/10) + pow((Num % 10) , 2);
    }
    return pow(Num,3);
}
int main ()
{
    int i = 0 ;
    for (i = 100 ; i <= 999 ; i++)
    {
        if(Pan_ShuiXian(i) == i)
        {
            printf("%d ",i);
        }
    }
    return 0;
}