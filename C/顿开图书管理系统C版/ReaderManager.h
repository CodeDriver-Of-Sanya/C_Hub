#ifndef _READERMANAGER_H_
#define _READERMANAGER_H_
#include"Reader.h"
#include"List.h"

typedef struct ReaderManager
{
	List readerList;//读者信息链表


}ReaderManager;

void readerManager_init(ReaderManager* rm);

//加载数据
void readerManager_loadData(ReaderManager* rm, const char* filename);

void readerManager_operation(ReaderManager* rm);

void readerManager_add(ReaderManager* rm);

void readerManager_modify(ReaderManager* rm);

void readerManager_remove(ReaderManager* rm);

void readerManager_search(ReaderManager* rm);

void readerManager_show(ReaderManager* rm);

#endif // !_READERMANAGER_H_
