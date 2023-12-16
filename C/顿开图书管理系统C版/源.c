#include"Menu.h"
#include"list.h"
#include"SeqList.h"
#include "UserManager.h"

#include<stdio.h>
#include<stdlib.h>

int main() 
{
	UserManager userManager;
	userManager_init(&userManager);

	while (1)
	{
		system("cls");
		switch (mainMenu())
		{
		case 0:
			quit();
			break;
		case 1:
			system("cls");
			userManager_operation(&userManager);
			break;
		case 2:
			system("cls");
			readerMenu();
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

	return 0;
}