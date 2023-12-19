#ifndef _BOOKMANAGE_H_
#define _BOOKMANAGE_H_
#include "Configure.h"
#include"SeqList.h"
#include"Book.h"

typedef struct BookManage
{
	SeqList books;//图书顺序表


}BookManage;

//初始化
void bookManage_init(BookManage* bm);
//加载数据
void bookManage_loadData(BookManage* bm, const char* filename);
//操作
void bookManage_operation(BookManage* bm);
//图书信息添加
void bookManage_add(BookManage* bm);
//图书信息修改
void bookManage_modify(BookManage* bm);
//图书信息查询
void bookManage_search(BookManage* bm);
//图书信息汇总
void bookManage_statistics(BookManage* bm);

//查询
//按书号查询
void bookManage_search_byBookNo(BookManage* bm);

//按书名查询
void bookManage_search_byBookName(BookManage* bm);

//按作者查询
void bookManage_search_byAuthor(BookManage* bm);

//按出版社查询
void bookManage_search_byPublish(BookManage* bm);

#endif // !_BOOKMANAGE_H_
