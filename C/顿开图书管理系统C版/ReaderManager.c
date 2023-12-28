#include "ReaderManager.h"
#include "Menu.h"

void readerManager_init(ReaderManager* rm)
{
	list_init(&rm->readerList);
	readerManager_loadData(rm, "./data/reader.txt");
}

void readerManager_loadData(ReaderManager* rm, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp) 
	{
		perror("reader.txt open failed!\n");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);//这行读的是表头
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		Reader* r = createEmptyReader();
		int ret = sscanf(buf, "%llu %s %s %s %d %d", &r->readerID, r->name, r->unit, r->tel, &r->borrowNum, &r->borrowedNum);
		if (ret <= 0)
		{
			printf("loadReaderData failed!\n");
			system("pause");
			break;
		}
		list_pushBack(&rm->readerList, r);
	}

	fclose(fp);
}

void readerManager_operation(ReaderManager* rm)
{
	bool isCyc = true;
	while (isCyc)
	{
		system("cls");
		switch (readerMenu())
		{
		case 0:
			isCyc = false;
			break;
		case 1:
			readerManager_add(rm);
			break;
		case 2:
			readerManager_modify(rm);
			break;
		case 3:
			readerManager_remove(rm);
			break;
		case 4:
			readerManager_search(rm);
			break;
		case 5:
			readerManager_show(rm);
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}

void readerManager_add(ReaderManager* rm)
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
		return;
	}
	Reader* newR = createEmptyReader();
	printf("请输入读者（读者号 读者名 单位 联系方式）：");
	scanf("%llu %s %s %s", &newR->readerID, newR->name, newR->unit, newR->tel);
	newR->borrowNum = 10;
	newR->borrowedNum = 0;
	list_pushBack(&rm->readerList, newR);
	printf("读者新建成功！\n");
	system("pause");
}

void readerManager_modify(ReaderManager* rm)
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
		return;
	}
	unsigned long long destID;
	printf("请输入要修改的读者号：");
	scanf("%llu", &destID);
	Reader* destR = list_search(&rm->readerList, reader_cmpID, destID);
	if (!destR)
	{
		printf("未找到读者号为 %llu 的读者\n", destID);
		return;
	}
	printf("请输入新的联系方式：");
	scanf("%s", &destR->tel);
	printf("修改成功！\n");
	system("pause");
}

void readerManager_remove(ReaderManager* rm)
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
		return;
	}
	unsigned long long destID;
	printf("请输入要删除的读者号：");
	scanf("%llu", &destID);
	Reader* destR = list_search(&rm->readerList, reader_cmpID, destID);
	if (!destR)
	{
		printf("未找到读者号为 %llu 的读者\n", destID);
		system("pause");
		return;
	}
	list_removeOne(&rm->readerList, destR);
	printf("删除成功\n");
	system("pause");
}

void readerManager_search(ReaderManager* rm)
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
		return;
	}
	unsigned long long destID;
	printf("请输入要查找的读者号：");
	scanf("%llu", &destID);
	Reader* destR = list_search(&rm->readerList, reader_cmpID, destID);
	if (!destR)
	{
		printf("未找到读者号为 %llu 的读者\n", destID);
		system("pause");
		return;
	}

	reader_print(destR);
	system("pause");

}

void readerManager_show(ReaderManager* rm)
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
		return;
	}
	list_transfrom(&rm->readerList, reader_print);
	system("pause");
}
