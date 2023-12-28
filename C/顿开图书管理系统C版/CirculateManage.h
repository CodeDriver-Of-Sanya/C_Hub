#ifndef _CIRCULATEMANAGE_H_
#define _CIRCULATEMANAGE_H_
#include "Configure.h"
#include "List.h"
#include "Circulate.h"
#include "Menu.h"
#include"BookManage.h"

typedef struct CirculateManage
{
	List cirList;
	BookManage* pbm;//指向图书管理的指针（借还书会用到）

}CirculateManage;

void cirManage_init(CirculateManage* cm, BookManage* bm);

void cirManage_loadData(CirculateManage* cm,const char* filename);

void cirManage_operation(CirculateManage* cm);

void cirManage_borrowBook(CirculateManage* cm);

void cirManage_returnBook(CirculateManage* cm);



#endif // !_CIRCULATEMANAGE_H_
