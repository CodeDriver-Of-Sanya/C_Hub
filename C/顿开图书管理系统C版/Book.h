#ifndef _BOOK_H_
#define _BOOK_H_
#include"Configure.h"

typedef struct Book
{
	int recordNo;//记录号
	int bookNo;//书号
	char name[20];//书名
	char author[20];//作者
	char publish[20];//出版社
	int bookNum;//藏书量
	int lendNum;//已借出量
	//三个索引
	int p1;
	int p2;
	int p3;
}Book;

//创建空图书
Book* createEmptyBook();

//根据字符串创建图书
Book* book_byString(const char* s);

//输出图书信息
void book_print(Book* b);

#endif // !_BOOK_H_
