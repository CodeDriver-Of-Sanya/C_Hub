#include "BookManage.h"
#include"Menu.h"

void bookManage_init(BookManage* bm)
{
	SeqList_init(&bm->books);
	bookManage_loadData(bm,"./data/book/books.txt");
}

void bookManage_loadData(BookManage* bm, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (!fp)
	{
		perror("bookManage_loadData fopen failed!\n");
		return;
	}
	char buf[BUFSIZ] = { 0 };
	fgets(buf, BUFSIZ, fp);//先把表头读出来
	while (!feof(fp))
	{
		fgets(buf, BUFSIZ, fp);
		SeqList_pushBack(&bm->books, book_byString(buf));
	}


	fclose(fp);
}

void bookManage_operation(BookManage* bm)
{
	bool isCyc = true;
	while (isCyc)
	{
		system("cls");
		switch (bookMenu())
		{
		case 0:
			isCyc = false;
			break;
		case 1:
			bookManage_add(bm);
			break;
		case 2:
			bookManage_modify(bm);
			break;
		case 3:
			bookManage_search(bm);
			break;
		case 4:
			bookManage_statistics(bm);
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}

void bookManage_add(BookManage* bm)
{
	Book* b = createEmptyBook();
	printf("请输入要添加的图书信息（书号 书名 作者 出版社 藏书量）：");
	int ret = scanf("%d %s %s %s %d", &b->bookNo, b->name, b->author, b->publish, &b->bookNum);
	if (ret != 5)
	{
		printf("输入图书信息有误！添加失败！\n");
		free(b);
		system("pause");
		return;
	}
	SeqList_pushBack(&bm->books, b);
	printf("添加成功！\n");
	system("pause");
	return;
}

void bookManage_modify(BookManage* bm)
{
	int destBookNo;
	printf("请输入要修改的书号：");
	scanf("%d", &destBookNo);

	foreach(Book * b, &bm->books)
	{
		if (b->bookNo == destBookNo)
		{
			printf("请输入修改后的信息（藏书量 借出数）：");
			int ret = scanf("%d %d", &b->bookNum, &b->lendNum);
			if (ret == 2)
			{
				printf("图书修改成功！\n");
				system("pause");
				return;
			}
			printf("图书修改失败！\n");
			system("pause");
			return;
		}
	}
	printf("未找到书号为 %d 的书号！\n", destBookNo);
	system("pause");
}

void bookManage_search(BookManage* bm)
{
	bool isCyc = true;
	while (isCyc)
	{
		system("cls");
		switch (bookSearchMenu())
		{
		case 0:
			isCyc = false;
			break;
		case 1:
			bookManage_search_byBookNo(bm);
			break;
		case 2:
			bookManage_search_byBookName(bm);
			break;
		case 3:
			bookManage_search_byAuthor(bm);
			break;
		case 4:
			bookManage_search_byPublish(bm);
			break;
		default:
			printf("输入的选项有误！请重新输入！\n");
			system("pause");
			break;
		}
	}
}

void bookManage_statistics(BookManage* bm)
{
	//统计总共有多少本书
	int cnt = 0;
	foreach(Book * b, &bm->books)
	{
		cnt += b->bookNum;
	}
	printf("图书馆总藏书【%d】本\n",cnt);
	system("pause");
}

void bookManage_search_byBookNo(BookManage* bm)
{
	int destBookNo = -1;
	bool isFind = false;
	printf("请输入要查询的图书号：");
	scanf("%d", &destBookNo);
	foreach(Book * b, &bm->books)
	{
		if (b->bookNo == destBookNo)
		{
			book_print(b);
			isFind = true;
		}
	}
	if (isFind) {
		system("pause");
	}
	else {
		printf("未找到书号为 %d 的书！\n", destBookNo);
		system("pause");
	}
	return;
}

void bookManage_search_byBookName(BookManage* bm)
{
	char destBookName[20] = { 0 };
	bool isFind = false;
	printf("请输入要查询的图书名：");
	scanf("%s", destBookName);
	foreach(Book * b, &bm->books)
	{
		if (strcmp(b->name, destBookName)==0)
		{
			book_print(b);
			isFind = true;
		}
	}
	if (isFind) {
		system("pause");
	}
	else {
		printf("未找到书名为 %s 的书！\n", destBookName);
		system("pause");
	}
	
	return;
}

void bookManage_search_byAuthor(BookManage* bm)
{
	char destBookAuthor[20] = { 0 };
	bool isFind = false;
	printf("请输入要查询的图书作者：");
	scanf("%s", destBookAuthor);
	foreach(Book * b, &bm->books)
	{
		if (strcmp(b->author, destBookAuthor) == 0)
		{
			book_print(b);
			isFind = true;
		}
	}
	if (isFind) {
		system("pause");
	}
	else {
		printf("未找到作者为 %s 的书！\n", destBookAuthor);
		system("pause");
	}
	
	return;
}

void bookManage_search_byPublish(BookManage* bm)
{
	char destBookPublish[20] = {0};
	bool isFind = false;
	printf("请输入要查询的图书出版社：");
	scanf("%s", destBookPublish);
	foreach(Book * b, &bm->books)
	{
		if (strcmp(b->publish, destBookPublish) == 0)
		{
			book_print(b);
			isFind = true;
		}
	}
	if (isFind) {
		system("pause");
	}
	else {
		printf("未找到出版社为 %s 的书！\n", destBookPublish);
		system("pause");
	}
	
	return;
}
