#include "ReaderManager.h"
#include"Menu.h"

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

}

void readerManager_modify(ReaderManager* rm)
{
}

void readerManager_remove(ReaderManager* rm)
{
}

void readerManager_search(ReaderManager* rm)
{
}

void readerManager_show(ReaderManager* rm)
{
	list_transfrom(&rm->readerList, reader_print);
	system("pause");
}
