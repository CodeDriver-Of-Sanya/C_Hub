#include"Menu.h"
#include"list.h"
#include"SeqList.h"
#include "UserManager.h"
#include"ReaderManager.h"

#include<stdio.h>
#include<stdlib.h>

//主管理系统
typedef struct ManageMent 
{
	UserManager userManager;//用户管理模块
	ReaderManager readerManager;//读者管理模块

}ManageMent;

void management_init(ManageMent* mm)
{
	userManager_init(&mm->userManager);
	readerManager_init(&mm->readerManager);
}

void management_login(ManageMent* mm)
{
	//登录模块
	unsigned long long login_ID;
	char login_pw[10] = { 0 };
	bool ret = false;//是否登录成功
	int loginCnt = 3;//最多失败三次

	do
	{
		system("cls");
		printf("请输入用户名：");
		scanf("%llu", &login_ID);
		printf("请输入密码：");
		//scanf("%s", login_pw);
		getchar();//清除缓冲区中的\n
		gets_s(login_pw, 10);
		//验证登录是否成功
		ret = userManager_login(&mm->userManager, login_ID, login_pw);
		if (ret)
		{
			printf("登录成功！\n");
			system("pause");
		}
		else {
			loginCnt--;
			printf("账号或密码错误！请重新输入！\n");
			system("pause");
		}
		if (0 == loginCnt)
		{
			printf("您已失败三次登录，即将为您退出系统！\n");
			system("pause");
			exit(0);
		}

	} while (!ret);
}

void management_quit(ManageMent* mm)
{
	exit(0);
}

//主菜单主循环
void management_run(ManageMent* mm)
{
	management_login(mm);
	while (1)
	{
		system("cls");
		switch (mainMenu())
		{
		case 0:
			management_quit(mm);
			break;
		case 1:
			system("cls");
			userManager_operation(&mm->userManager);
			break;
		case 2:
			system("cls");
			readerManager_operation(&mm->readerManager);
			break;
		case 3:
			system("cls");
			bookMenu();
			break;
		case 4:
			system("cls");
			bookCirculateMenu();
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}


int main() 
{
	ManageMent m;
	management_init(&m);

	management_run(&m);

	return 0;
}