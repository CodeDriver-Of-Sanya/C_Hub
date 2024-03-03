#include "BookManage.h"
#include"Menu.h"
#include"BookIndex.h"
#include"BookIndex.h"

static bool canOp()
{
	extern User* global_curUser;
	if (!is_bookAdmin(global_curUser))
	{
		printf("当前登录的用户无权进行此操作！\n");
		system("pause");
	}
}

void bookManage_init(BookManage* bm, const char* filename)
{
	SeqList_init(&bm->books);
	SeqList_init(&bm->bookNameIndexList);
	SeqList_init(&bm->bookAuthorIndexList);
	SeqList_init(&bm->bookPublishIndexList);
	strcpy(bm->filename, filename);
	bookManage_loadData(bm, filename);
	bm->useIndex = false;//默认不使用索引
	bookManage_createIndex(bm);
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

bool isInIdxList(SeqList* sl, const char * c)
{
	foreach(BookIndex * bi, sl)
	{
		if (0 == strcmp(bi->str, c))
		{
			return true;
		}
	}
	return false;
}

void bookManage_createIndex(BookManage* bm)
{
	
	bm->useIndex = true;
	//1.建立 图书(书名，作者，出版社) 关键字索引（到p1，p2，p3）
	//从大到小倒序遍历（每本都指向前一本）
	for (int i = bm->books.size-1; i >= 0; i--)
	{
		Book* b1 = bm->books.pparr[i];
		//同时找三个索引
		bool isFindName = false;
		bool isFindAuthor = false;
		bool isFindPublish = false;
		//跟前面的每本都再遍历一次,一一对比
		for (int j = i - 1; j >= 0; j--)
		{
			Book* b2 = bm->books.pparr[j];
			//如果name相同，将此index给指针1（p1）
			if (!isFindName && 0 == strcmp(b1->name, b2->name))
			{
				b1->p1 = j+1;
				isFindName = true;
			}
			//同理
			if (!isFindAuthor && 0 == strcmp(b1->author, b2->author))
			{
				b1->p2 = j+1;
				isFindAuthor = true;
			}
			if (!isFindPublish && 0 == strcmp(b1->publish, b2->publish))
			{
				b1->p3 = j+1;
				isFindPublish = true;
			}

		}

	}
	
	/*foreach(Book * b, &bm->books)
	{
		book_print(b);
	}
	system("pause");*/

	//建立 次关键字 索引
	for (int i = bm->books.size - 1; i >= 0; i--)
	{
		Book* b1 = bm->books.pparr[i];
		//2.建立 书名 次关键字索引
		//如果没有在对应的次索引表出现过，那就插入
		if (!isInIdxList(&bm->bookNameIndexList, b1->name))
		{
			BookIndex* bi = createEmptyBookIndex();
			strcpy(bi->str, b1->name);
			bi->point = i+1;
			int cnt = 0;
			foreach(Book * b, &bm->books)
			{
				if (0 == strcmp(b->name, b1->name))
				{
					cnt++;
				}
			}
			bi->length = cnt;
			SeqList_pushBack(&bm->bookNameIndexList, bi);
		}
		//3.建立 作者 次关键字索引
		if (!isInIdxList(&bm->bookAuthorIndexList, b1->author))
		{
			BookIndex* bi = createEmptyBookIndex();
			strcpy(bi->str, b1->author);
			bi->point = i+1;
			int cnt = 0;
			foreach(Book * b, &bm->books)
			{
				if (0 == strcmp(b->author, b1->author))
				{
					cnt++;
				}
			}
			bi->length = cnt;
			SeqList_pushBack(&bm->bookAuthorIndexList, bi);
		}
		//4.建立 出版社 次关键字索引
		if (!isInIdxList(&bm->bookPublishIndexList, b1->publish))
		{
			BookIndex* bi = createEmptyBookIndex();
			strcpy(bi->str, b1->publish);
			bi->point = i+1;
			int cnt = 0;
			foreach(Book * b, &bm->books)
			{
				if (0 == strcmp(b->publish, b1->publish))
				{
					cnt++;
				}
			}
			bi->length = cnt;
			SeqList_pushBack(&bm->bookPublishIndexList, bi);
		}
	}
	/*foreach(BookIndex * bi, &bm->bookNameIndexList)
	{
		bookIndex_print(bi);
	}
	printf("-----------------------------------\n");
	foreach(BookIndex* bi, &bm->bookAuthorIndexList)
	{
		bookIndex_print(bi);
	}
	printf("-----------------------------------\n");
	foreach(BookIndex* bi, &bm->bookPublishIndexList)
	{
		bookIndex_print(bi);
	}
	system("pause");*/
}

void bookManage_destoryIndex(BookManage* bm)
{
	bm->useIndex = false;
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
	if (!canOp())return;
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
	if (!canOp())return;
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
	if (!canOp())return;
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
	if (!canOp())return;
	//统计总共有多少本书
	int cnt = 0;
	foreach(Book * b, &bm->books)
	{
		cnt += b->bookNum;
	}
	printf("图书馆总藏书【%d】本\n",cnt);
	system("pause");
}

void bookManage_quit(BookManage* bm)
{
	//信息保存到文件
	FILE* fp = fopen(bm->filename, "w");
	if (!fp)
	{
		perror("bookManage_quit fopen failed!\n");
		return;
	}


	fclose(fp);
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
	if (!bm->useIndex)
	{
		foreach(Book * b, &bm->books)
		{
			if (strcmp(b->name, destBookName) == 0)
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
	}
	else
	{
		Book* searched = NULL;
		foreach(BookIndex * bi, &bm->bookNameIndexList)
		{
			if (strcmp(bi->str, destBookName) == 0)
			{
				int searchedIdx = bi->point;
				while (searchedIdx)
				{
					searched = bm->books.pparr[searchedIdx-1];
					book_print(searched);
					searchedIdx = searched->p1;
				}
				system("pause");
				return;
			}
		}
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
