#ifndef _BOOKMANAGE_H_
#define _BOOKMANAGE_H_
#include "Configure.h"
#include"SeqList.h"
#include"Book.h"

typedef struct BookManage
{
	SeqList books;//图书顺序表
	SeqList bookNameIndexList;//书名索引表
	SeqList bookAuthorIndexList;//作者索引表
	SeqList bookPublishIndexList;//出版社索引表
	char filename[128];//存储信息文件的路径
	bool useIndex;//是否使用索引


}BookManage;

//初始化
void bookManage_init(BookManage* bm,const char* filename);
//加载数据
void bookManage_loadData(BookManage* bm, const char* filename);

//建立索引表
void bookManage_createIndex(BookManage* bm);

//销毁索引表
void bookManage_destoryIndex(BookManage* bm);


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
//退出子系统
void bookManage_quit(BookManage* bm);

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
