#include "Menu.h"
#include<stdio.h>

int mainMenu()
{
    printf("**************=**************\n");
    printf("*        1.用户管理         *\n");
    printf("*        2.读者管理         *\n");
    printf("*        3.图书管理         *\n");
    printf("*        4.图书流通管理     *\n");
    printf("*        0.退出系统         *\n");
    printf("**************=**************\n");

    return select();
}

int userMenu()
{
    printf("**********=用户管理=**********\n");
    printf("*        1.用户信息添加      *\n");
    printf("*        2.用户信息修改      *\n");
    printf("*        3.用户信息删除      *\n");
    printf("*        4.用户信息显示      *\n");
    printf("*        5.用户密码修改      *\n");
    printf("*        0.返回主菜单        *\n");
    printf("**********=********=**********\n");
    return select();
}

int readerMenu()
{
    printf("**********=读者管理=**********\n");
    printf("*        1.读者信息添加      *\n");
    printf("*        2.读者信息修改      *\n");
    printf("*        3.读者信息删除      *\n");
    printf("*        4.读者信息查询      *\n");
    printf("*        5.读者信息显示      *\n");
    printf("*        0.返回主菜单        *\n");
    printf("**********=********=**********\n");
    return select();
}

int bookMenu()
{
    printf("**********=图书管理=**********\n");
    printf("*        1.图书信息添加      *\n");
    printf("*        2.图书信息修改      *\n");
    printf("*        3.图书信息查询      *\n");
    printf("*        4.汇总统计          *\n");
    printf("*        0.返回主菜单        *\n");
    printf("**********=********=**********\n");
    return select();
}

int bookSearchMenu()
{
    printf("********=图书信息查询=********\n");
    printf("*      1.按书号查询          *\n");
    printf("*      2.按书名查询          *\n");
    printf("*      3.按作者查询          *\n");
    printf("*      4.按出版社查询        *\n");
    printf("*      0.返回主菜单          *\n");
    printf("********=************=********\n");
    return select();
}

int bookCirculateMenu()
{
    printf("********=图书流通管理=********\n");
    printf("*      1.借书处理            *\n");
    printf("*      2.还书处理            *\n");
    printf("*      0.返回主菜单          *\n");
    printf("********=************=********\n");
    return select();
}

int select()
{
    int s = -1;
    printf("请输入选项：");
    scanf("%d", &s);
    return s;
}

void quit()
{
    exit(0);
}
