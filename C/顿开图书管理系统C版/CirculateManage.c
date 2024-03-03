#include "CirculateManage.h"

static bool canOp()
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
	}
}

void cirManage_init(CirculateManage* cm, BookManage* bm)
{
	list_init(&cm->cirList);
	cm->pbm = bm;
	cirManage_loadData(cm, "./data/circulate.txt");
}

void cirManage_loadData(CirculateManage* cm, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("cirManage_loadData failed!\n");
		return;
	}

	char buf[BUFSIZ] = { 0 };
	fgets(buf,BUFSIZ,fp);
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		list_pushBack(&cm->cirList, createByStr(buf));
	}

	fclose(fp);
	//list_transfrom(&cm->cirList, cir_print);
	//system("pause");
}

void cirManage_operation(CirculateManage* cm)
{
	bool isCyc = true;
	while (isCyc)
	{
		system("cls");
		switch (bookCirculateMenu())
		{
		case 0:
			isCyc = false;
			break;
		case 1:
			cirManage_borrowBook(cm);
			break;
		case 2:
			cirManage_returnBook(cm);
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}

void cirManage_borrowBook(CirculateManage* cm)
{
	if (!canOp())return;
	printf("请输入新的借书信息（读者号 书号 借书日期）：");
	Circulate* c = createEmptyCir();
	int ret = scanf("%llu %d %s", &c->readerID, &c->bookNo, c->borrowData);
	if (ret != 3)
	{
		printf("输入的信息有误，添加失败！\n");
		system("pause");
		free(c);
		return;
	}

	list_pushBack(&cm->cirList, c);
	printf("借书信息添加成功！\n");
	system("pause");

	//让该图书借出数+1
	foreach(Book * book, &cm->pbm->books)
	{
		if (book->bookNo == c->bookNo)
		{
			book->lendNum++;
		}
	}

}

bool cmpCir(Circulate* c1, Circulate* c2)
{
	return c1->readerID == c2->readerID && c1->bookNo == c2->bookNo;
}
void cirManage_returnBook(CirculateManage* cm)
{
	if (!canOp())return;
	printf("请输入还书信息（读者号 书号）：");
	Circulate c;
	int ret = scanf("%llu %d", &c.readerID, &c.bookNo);
	if (ret != 2)
	{
		printf("输入的信息有误，操作失败！\n");
		system("pause");
		return;
	}

	//查找有没有该读者和借书信息
	Circulate* pret = list_search(&cm->cirList, cmpCir, &c);
	if (!pret)
	{
		printf("没有找到此借书信息！\n");
		system("pause");
		return;
	}
	list_removeOne(&cm->cirList, pret);
	printf("还书成功！\n");
	system("pause");

	//该图书的借出数-1
	foreach(Book * book, &cm->pbm->books)
	{
		if (book->bookNo == c.bookNo)
		{
			book->lendNum--;
		}
	}

}
